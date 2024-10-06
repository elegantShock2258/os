#pragma once
#include "kheap.h"

// kernel_end is defined in the linker script.
extern u32 kernel_end;
u32 heap_start = (u32)&kernel_end;

BitMapColumn BitMap[1]; // 1*32*1 bytes

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
void init_bitmap() {
  BitMap[0].column = (bitColumn *)0x00000000;
  BitMap[0].baseAddress = (u32 *)heap_start;
  BitMap[0].endAddress = (u32 *)(heap_start + sizeof(char) * 32);
}

// 0 -> free
// 1 -> used

// 00010101001000010000000000000001 ->
// 00000000000000000000000000000000
// 00000000000000000000000000000000
// 00000000000000000000000000000000
// 00000000000000000000000000000000
// 00000000000000000000000000000000
// 00000000000000000000000*11111111 , the * is MEM_END, notice how the mem end
// is NOT necessarily in the end of bitmap (to maintain structure) define a
// mem_end as the nth bit in the last column of the bitmap. everytime check if
// the allocated/deallocated block is before mem_end. MAP all blocks available
// in the memory pool if cant fit within a row, allocate 1s

void *kmalloc(u32 size) {

  u32 mem = heap_start;
  heap_start += size;
  return (void *)mem;
}

void *kmalloc_page() {
  if (heap_start & 0xFFFFF000) { // not alligned
                                 // Align the placement address;
    heap_start &= 0xFFFFF000;
    heap_start += 0x1000;
  }
  return kmalloc(0x1000);
}