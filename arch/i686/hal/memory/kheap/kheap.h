
#ifndef KHEAP_H
#define KHEAP_H

#include "../../../../../utils/kernel_utils.c"

void* kmalloc(u32 size);
void* kmalloc_page();

#endif