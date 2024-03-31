#include "../../utils/kernel_utils.c"
#include "../../utils/types.h"
#ifndef ___GDTC

#define ___GDTC

struct gdtr {
  u16 limit;               // -> size of GDT
  u32 base;                // -> ptr to GDT
} __attribute__((packed)); // do the attribute shit so gcc doesnt include some
                           // optimisation bits
typedef struct gdtr gdtr;

//---------------------------------------------------------------------------------------------
// Look at the GDT Entry picture to understand the stuct
// Limit 0:7 Limit 8:15 Base 0:7 base 7:15 base 16:23 Access Byte Flags Limit
// 16:19 Base 24:91
//---------------------------------------------------------------------------------------------
struct gdt_entry {
  // theres only one base thing i think, for some reason its distributed like in
  // the pic
  u16 limit_low;
  u16 base_low;
  u8 base_middle;
  u8 access;
  u8 granularity; // this includes the flags and limits in the pic
  u8 base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry;

struct gdt_ptr {
  u16 limit;       // start address
  gdt_entry *base; // size
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr;

gdt_entry gdt_entries[7];

extern void gdt_flush(u32);

/**
 * @brief Sets the information for a GDT entry.
 *
 * @param num The index of the GDT entry to set.
 * @param base The base address of the segment.
 * @param limit The size of the segment, in bytes.
 * @param access The access flags for the segment.
 * @param gran The granularity of the segment.
 */
static void gdt_set_entry_info(u32 num, u32 base, u32 limit, u8 access,
                               u8 gran) {
  gdt_entries[num].base_low = (base & 0xFFFF);
  gdt_entries[num].base_middle = (base >> 16) & 0xFF;
  gdt_entries[num].base_high = (base >> 24) & 0xFF;

  gdt_entries[num].limit_low = (limit & 0xFFFF);

  gdt_entries[num].access = access;

  gdt_entries[num].granularity = gran;
}

// ill add these entries to the GDT
// some null entry first too
// "code": kernel code, used to stored the executable binary code
// "data": kernel data
// "stack": kernel stack, used to stored the call stack during kernel execution
// "ucode": user code, used to stored the executable binary code for user
// program
// "udata": user program data
// "ustack": user stack, used to stored the call stack during execution in
// userland

void gdt_init() {
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

  kernel_log("GDT: Set GDT.\n");
}
#endif