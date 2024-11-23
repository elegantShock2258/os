#pragma once
#include "../../../../utils/kernel_utils.c"

typedef struct Window{
    int x,y; // x,y coordinates of top left corner
    int width, height; // width and height of the window

    u32* windowFb;
    
} Window;