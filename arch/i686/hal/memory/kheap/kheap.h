#pragma once

#define BLOCKSIZE 2048 * sizeof(u32) // bytes per block
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
