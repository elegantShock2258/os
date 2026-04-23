#pragma once
#include "../../../arch/i686/hal/memory/kheap/kheap.c"
#include "../../../utils/kernel_utils.c"

void *malloc(u32 size) {
  return kmalloc(size);
}