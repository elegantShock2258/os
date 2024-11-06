#pragma once
#include "./mmap.h"
void *malloc(u32 size) { return kmalloc(size); }
void *free(void* ptr) { return kfree(ptr); }