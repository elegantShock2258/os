#pragma once

#define BLOCKSIZE (sizeof(char)*(1<<20)) // bytes per block, make SURE of including the () THE MULTIPLICATION WILL FUCK UP THE CALCULATIONS
#include "../../../../../utils/kernel_utils.c"
#include "../memory.c"
void *kmalloc(u32 size);
void *kmalloc_page();

typedef u32 bitColumn;
typedef struct {
  bitColumn column;
  u32 *baseAddress;
  u32 *endAddress;
} BitMapColumn;
