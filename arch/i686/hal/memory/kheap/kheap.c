#pragma once
#include "kheap.h"
#define BitMapSize 1

// kernel_end is defined in the linker script.
extern u32 kernel_end;
u32 heap_start = (u32)&kernel_end;

BitMapColumn
    BitMap[BitMapSize]; // 1 column * 32 blocks / column * 1024 bytes per block

// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
void init_bitmap(u32 ebx) {
  multiboot_info_t *mbd = (multiboot_info_t *)ebx;
  // start is heap_start
  // get end from multiboot
  u32 end_addr = -1;
  u32 mem_size = -1;
  if (!(mbd->flags >> 6 & 0x1)) {
    printf("invalid memory map given by GRUB bootloader\n");
  }
  for (int i = 0; i < mbd->mmap_length; i += sizeof(memory_map_t)) {
    memory_map_t *mmmt = (memory_map_t *)(mbd->mmap_addr + i);
    if (mmmt->type == 1) {
      end_addr = mmmt->base_addr_high;
      mem_size = mmmt->base_addr_high - mmmt->base_addr_low;
    }
  }
  // calculate number of columns in bitmap
  u32 numColumns = (mem_size / (BLOCKSIZE * 32)) + 1;
  // calculate the blockend for the last column in the bitmap

  // for all n-1 columns, jus do the following:
  BitMap[0].column = 0x00000000; // all blocks are free
  BitMap[0].baseAddress = (u32 *)heap_start;
  BitMap[0].endAddress = (u32 *)(heap_start + BLOCKSIZE * 32);
  for (int i = 1; i <= numColumns; i++) {
    BitMap[i].column = 0x00000000; // all blocks are free
    BitMap[i].baseAddress = (u32 *)BitMap[i - 1].endAddress;
    BitMap[i].endAddress = (u32 *)(BitMap[i].baseAddress + BLOCKSIZE * 32);
  }
  int n = 0;
  for (u32 *m0 = BitMap[numColumns].baseAddress; m0 < (u32 *)end_addr;
       m0 += BLOCKSIZE) {
    ++n;
  }
  // for the last one make sure to put the endAddress till the blockend, and
  // make everybit as busy
  for (int i = n; i < 32; i++)
    setNthBit(&BitMap[numColumns].column, i, true);
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
  // if ALL memory is filled, jus return a full address of all ones for now
  if (column == -1)
    return (void *)0xffffffff;
  // assign as busy in the bitmap
  setNthBit(&BitMap[column].column, blockPosition, true);
  // return the address
  return (void *)(BitMap[column].baseAddress + BLOCKSIZE * blockPosition);
}
void *kfree(void *pointer) {
  // get the block position
  // address = start_address + (BLOCKSIZE * blockPosition) +
  // 32*BLOCKSIZE*(column-1);
  u32 pointerAddressOffset = (u32)pointer - heap_start;
  // pointerAddressOffset =  (BLOCKSIZE * blockPosition) +
  // 32*BLOCKSIZE*(column-1);
  u32 positions = pointerAddressOffset / BLOCKSIZE;
  // pointerAddressOffset =  (blockPosition) + 32*(column-1);
  u32 blockPosition = positions % 32;
  u32 column = ((positions - blockPosition) / 32) + 1;

  // mark as free
  setNthBit(&BitMap[column].column, blockPosition, false);
  // memset as clear???
  memset(pointer, 0, BLOCKSIZE);
  return NULL;
}

void *kmalloc_page() {
  if (heap_start & 0xFFFFF000) { // not alligned
                                 // Align the placement address;
    heap_start &= 0xFFFFF000;
    heap_start += 0x1000;
  }
  return kmalloc(0x1000);
}