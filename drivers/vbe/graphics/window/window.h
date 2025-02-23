#pragma once
#include "../../../../utils/kernel_utils.c"
#include "../../../../utils/ds/AvlTree/AvlTree.c"
#include "../../vbe.c"
#include "../../../../arch/i686/hal/memory/memory.c"

typedef struct Window{
    u32 x,y; // x,y coordinates of top left corner
    u32 width, height; // width and height of the window
    u32 zIndex;
    u32* windowFb;
    
} Window;