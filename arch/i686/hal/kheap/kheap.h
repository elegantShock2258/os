
#ifndef KHEAP_H
#define KHEAP_H

#include "../../../../utils/kernel_utils.c"

void* kmalloc(u32 size);
u32 kmalloc_page();

#endif