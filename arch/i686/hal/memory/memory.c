#pragma once
#include "memory.h"

#include "../../../../utils/kernel_utils.c"
void* memcpy(void* dst, const void* src, uint32_t num)
{
    uint32_t* u32Dst = (uint32_t *)dst;
    const uint32_t* u32Src = (const uint32_t *)src;

    for (uint32_t i = 0; i < num; i++)
        u32Dst[i] = u32Src[i];

    return dst;
}

void * memset(void * ptr, int value, uint16_t num)
{
    u32* u8Ptr = (u32 *)ptr;

    for (uint16_t i = 0; i < num; i++)
        u8Ptr[i] = (uint8_t)value;

    return ptr;
}

int memcmp(const void* ptr1, const void* ptr2, uint16_t num)
{
    const u32* u8Ptr1 = (const u32 *)ptr1;
    const u32* u8Ptr2 = (const u32 *)ptr2;

    for (uint16_t i = 0; i < num; i++)
        if (u8Ptr1[i] != u8Ptr2[i])
            return 1;

    return 0;
}