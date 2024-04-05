#pragma once
#include "IDT.h"

__attribute__((aligned(0x10))) static IDTEntry idt[256];
void IDT_EnableGate(int interrupt) {
  FLAG_SET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}

void IDT_DisableGate(int interrupt) {
  FLAG_UNSET(idt[interrupt].Flags, IDT_FLAG_PRESENT);
}
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
  // kernel_log("IDT: done\n");
}
