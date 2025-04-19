#pragma once
#include "kheap.h"
#define BitMapSize 20
// FIXME: for some rerason the allocator doesnt allocate the bitset from the
// start of the column but in between some area?
// col: 00000000000 assign: 1111
// itll do 00011100000 instead of 111000000
//  kernel_end is defined in the linker script.
extern u32 kernel_end;
u32 heap_start = (u32)&kernel_end;

BitMapColumn BitMap[BitMapSize]; // 1 column * 32 bytes / column
bool kmallocInit = false;
void *kmalloc_primitive(u32 size) {
  // use only for backbuffer in vbe driver or to assign memory which will never
  // be needed to free
  // USE ONLY BEFORE BITMAP_INIT
  if (kmallocInit)
    return NULL; // SAFETY, TODO: can make it so you relocate the bitmap
  u32 addr = heap_start;
  heap_start += size;
  return (void *)addr;
}
// 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
void bitmap_init() {
  // TODO: fill bitmap till mem end
  u32 *start = (u32 *)heap_start;
  for (int i = 0; i < BitMapSize; i++) {
    BitMap[i].column = 0x00000000; // all blocks are free
    BitMap[i].baseAddress = start;
    BitMap[i].endAddress = (u32 *)(start + BLOCKSIZE * 32);
    start = BitMap[i].endAddress;
  }
// #ifndef debug
//   printf("INITAL COLUMN: ");
//   printBinary(BitMap[0].column);
// #endif
  kmallocInit = true;
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

int getContigousBlocks(u32 block, int blocksRequired) {

  int count = 0;
  for (int i = 31; i >= 0; i--) {
    if ((block & (1 << i)) == 0) {
      count++;
    } else {
      count = 0;
    }
    if (count == blocksRequired) {
      return (31 - i);
    }
  }
  return -1;
}
void printBitmap() {
  printf("---Bitmap---\n");
  for (int i = 0; i < BitMapSize; i++)
    printBinary(BitMap[i].column);
}
void logBitmap() {
  for (int i = 0; i < BitMapSize; i++)
   logBinary(BitMap[i].column);
}
void *kmalloc(u32 size) {
  // we can have two cases here
  // 1) size can fit in one block -> assign the block
  // 2) size cant fit in one block -> assign blocks (contiguous blocks) in a
  // column, if cant find goto next column get a free block
  // for now for simplicity ill only assume the first case to take place

  // for the second one, well return a address which will be as follows:
  // start address of the block will just contain the address of the next block
  // if required, otherwise only one block is required, use 0xffffffff for the
  // next ptr

  // so in the code caluculate the address as follows
  // addr = BitMap[initialColumn].baseAddress + BLOCKSIZE * blockPosition
  // but, just set the value of the addr as the int for how many blocks are
  // associated,
  // *addr = blocks

  // so add some metadata for the next block so kfree knows about it
  // for now aim of the allocator is to allocate memory segments for pointers
  // despite the size, and de allocate them as necessary.

  int blockPosition;
  int initialColumn = -1;
  int sizeRequired = size + sizeof(int *);
  int blocksRequired = (sizeRequired / BLOCKSIZE) + 1;
  for (int i = 0; i < BitMapSize &&
                  BitMap[i].column !=
                      0xffffffff /* only go through blocks which are not full*/;
       i++) {
    bitColumn block = BitMap[i].column;

    blockPosition = getContigousBlocks(block, blocksRequired);
    if (blockPosition != -1) {
      initialColumn = i;
      break;
    }
  }
  if (initialColumn == -1)
    // kernel panic because memory cannot be allocated for the requested size
    return NULL;

  // assign as busy in the bitmap
  for (int i = blockPosition; i < blockPosition + blocksRequired; i++)
    setNthBit(&BitMap[initialColumn].column, i, true);

  void *address =
      (void *)(BitMap[initialColumn].baseAddress + BLOCKSIZE * blockPosition);

  // add a integer to denote how many consecutive blocks are present for the ptr
  *(int *)address = blocksRequired;


  return (address + sizeof(int));
}

void *kfree(void *pointer) {
  //  get the block position
  //  address = start_address + (BLOCKSIZE * blockPosition) +
  //  32*BLOCKSIZE*(column-1);
  int blocks = *(int *)(pointer - sizeof(int));
  u32 pointerAddressOffset = (u32)pointer - heap_start;
  // pointerAddressOffset =  (BLOCKSIZE * blockPosition) +
  // 32*BLOCKSIZE*(column-1);
  u32 positions = pointerAddressOffset / BLOCKSIZE;
  // pointerAddressOffset =  (blockPosition) + 32*(column-1);
  u32 initialBlockPosition = positions % 32;
  u32 column = ((positions - initialBlockPosition) / 32) + 1;
  // mark as free
  for (int i = initialBlockPosition; i < initialBlockPosition + blocks; i++)
    setNthBit(&BitMap[column].column, i, false);
  // memset as clear???
  memset(pointer, 0, BLOCKSIZE * blocks);
}