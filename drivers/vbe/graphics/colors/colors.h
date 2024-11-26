#pragma once
#include "../../../../utils/kernel_utils.c"


typedef struct Color {
    u8 r;
    u8 g;
    u8 b;
} Color;

#define COLOR(r, g, b) ((b) | (g << 8) | (r << 16))