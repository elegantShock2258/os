#pragma once
#include "kheap.h"

// kernel_end is defined in the linker script.
extern u32 kernel_end;
u32 placement_address = (u32)&kernel_end;

void *kmalloc(u32 size) {
  u32 mem = placement_address;
  placement_address += size;
  return (void *)mem;
}

void *kmalloc_page() {
  if (placement_address & 0xFFFFF000) { // not alligned
                                        // Align the placement address;
    placement_address &= 0xFFFFF000;
    placement_address += 0x1000;
  }
  return kmalloc(0x1000);
}