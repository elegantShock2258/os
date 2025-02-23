#pragma once
#include "../../../../utils/kernel_utils.c"
#include "../../vbe.h"
#include "../../../../arch/i686/hal/memory/memory.c"

typedef struct Window{
    int x,y; // x,y coordinates of top left corner
    int width, height; // width and height of the window

    u32* windowFb;
    
} Window;