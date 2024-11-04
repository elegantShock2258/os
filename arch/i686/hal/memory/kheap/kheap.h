#pragma once

#define BLOCKSIZE 1024*sizeof(char) // bytes per block
#include "../../../../../utils/kernel_utils.c"

void *kmalloc(u32 size);
void *kmalloc_page();


typedef u32 bitColumn;
typedef struct {
  bitColumn column;
  u32 *baseAddress;
  u32 *endAddress;
} BitMapColumn;
