#pragma once
#include "kheap.h"
#define BitMapSize 1

// kernel_end is defined in the linker script.
extern u32 kernel_end;
u32 heap_start = (u32)&kernel_end;

BitMapColumn BitMap[BitMapSize]; // 1 column * 32 bytes / column

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
void init_bitmap() {
  BitMap[0].column = 0x00000000; // all blocks are free
  BitMap[0].baseAddress = (u32 *)heap_start;
  BitMap[0].endAddress = (u32 *)(heap_start + sizeof(char) * 32);
}

// 0 -> free
// 1 -> used

// 00010101001000010000000000000001
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
  // get a free block
  int blockPosition;
  int column = -1;
  for (int i = 0; i < BitMapSize; i++) {
    bitColumn blocks = BitMap[i].column;
    blockPosition = findFirstUnSetBit(blocks);
    if (blockPosition == -1) {
      column = i;
      break;
    }
  }
  // assign as busy in the bitmap
  setNthBit(&BitMap[column].column, blockPosition, true);
  // return the address
  return (void *)(BitMap[column].baseAddress + BLOCKSIZE * blockPosition);
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