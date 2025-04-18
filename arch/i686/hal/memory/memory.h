#pragma once
#include "../../../../utils/kernel_utils.c"

#define SEG(off) (off>>16)
#define OFF(off) (off&0xffff)

#define SEGOFF2LIN(off) ((SEG(off) << 4) + OFF(off))


void* memcpy(void* dst, const void* src, uint32_t num);
int memcmp(const void* ptr1, const void* ptr2, uint16_t num);
