#pragma once
#include "gdt.h"
#include "../../utils/kernel_utils.c"

gdt_entry gdt_entries[7];

static void gdt_set_entry_info(u32 num, u32 base, u32 limit, u8 access,
                               u8 gran) {
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit_low = (limit & 0xFFFF);

  gdt_entries[num].access = access;

  gdt_entries[num].granularity = gran;
}
extern void reloadSegments();

void gdt_init() {
  asm("cli");
  gdt_ptr gdtPtr;
  gdtPtr.limit = (sizeof(gdt_entry) * 3) - 1;
  gdtPtr.base = &gdt_entries[0];

  gdt_set_entry_info(0, 0, 0, 0, 0); // Null segment
  kernel_log("GDT: Create NULL Segment: (%o,%o,%o,%o,%o)\n", 0, 0, 0, 0, 0);
  gdt_set_entry_info(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code segment
  kernel_log("GDT: Create Kernel Code Segment: (%o,%o,%o,%o,%o)\n", 1, 0,
             0xFFFFFFFF, 0x9A, 0xCF);
  gdt_set_entry_info(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data segment
  kernel_log("GDT: Create Kernel Data Segment: (%o,%o,%o,%o,%o)\n", 1, 0,
             0xFFFFFFFF, 0x92, 0xCF);
  gdt_set_entry_info(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code segment
  kernel_log("GDT: Create User Code Segment: (%o,%o,%o,%o,%o)\n", 1, 0,
             0xFFFFFFFF, 0xFA, 0xCF);
  gdt_set_entry_info(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Data segment
  kernel_log("GDT: Create User Data Segment: (%o,%o,%o,%o,%o)\n", 1, 0,
             0xFFFFFFFF, 0xF2, 0xCF);
  // TODO: figure out sizeof TSS and put as limit
  // gdt_set_entry_info(5, 0, 0xFFFFFFFF, 0x89, 0x0F); // Task State segment
  gdt_set_entry_info(5, 0, 0xFFFFFFFF, 0x89, 0xCF); //  Dummy Task State segment
  kernel_log("GDT: Create (Dummy) Task State Segment: (%o,%o,%o,%o,%o)\n", 1, 0,
             0xFFFFFFFF, 0x89, 0xCF);

  __asm__ volatile("lgdt %0" : : "m"(gdtPtr)); // load the new GDT

  reloadSegments();
  kernel_log("GDT: Set GDT.\n");
}