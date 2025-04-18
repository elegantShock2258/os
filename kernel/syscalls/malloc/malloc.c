#pragma  once
#include "../../../utils/kernel_utils.c"
#include "../../../arch/i686/hal/memory/kheap/kheap.c"

void* malloc(u32 size){
    return kmalloc(size);
}