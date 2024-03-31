#pragma once

#include "../../utils/binary.h"
#include "../../utils/kernel_utils.c"
#include "../../utils/types.h"

#define IDT_FLAG_GATE_TASK 0x5
#define IDT_FLAG_GATE_16BIT_INT 0x6
#define IDT_FLAG_GATE_16BIT_TRAP 0x7
#define IDT_FLAG_GATE_32BIT_INT 0xE
#define IDT_FLAG_GATE_32BIT_TRAP 0xF

#define IDT_FLAG_RING0 (0 << 5)
#define IDT_FLAG_RING1 (1 << 5)
#define IDT_FLAG_RING2 (2 << 5)
#define IDT_FLAG_RING3 (3 << 5)

#define IDT_FLAG_PRESENT 0x80

typedef struct {
  u16 BaseLow;
  u16 SegmentSelector;
  u8 Reserved;
  u8 Flags;
  u16 BaseHigh;
} __attribute__((packed)) IDTEntry;

__attribute__((aligned(0x10))) static IDTEntry idt[256];
void IDT_EnableGate(int interrupt) {
  if (interrupt < 10)
    printf("enabled %d\n", interrupt);
  FLAG_SET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_DisableGate(int interrupt) {
  FLAG_UNSET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

typedef struct {
  u16 limit;
  IDTEntry *base;
} __attribute__((packed)) idtr_t;

static idtr_t idtr;

void idt_set_descriptor(u8 interrupt, void (*base)(), u8 flags) {
  idt[interrupt].BaseLow = (u16) (((u32)base) & 0xFFFF);
  idt[interrupt].SegmentSelector = 0x08;
  idt[interrupt].Reserved = 0;
  idt[interrupt].Flags = flags;
  idt[interrupt].BaseHigh = (u16) (((u32)base >> 16) & 0xFFFF);

  // void (*s)() = (void(*)()) (idt[interrupt].BaseLow + ((idt[interrupt].BaseHigh) << 16));
  // s();
}

void idt_init() {
  idtr.base = &idt[0];
  idtr.limit = (u16)sizeof(IDTEntry) * (256 - 1);


  __asm__ volatile("lidt %0" : : "m"(idtr)); // load the new IDT
  __asm__ volatile("sti");                   // enable interrupts
  kernel_log("IDT: done\n");

}
