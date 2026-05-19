#pragma once
#include "../../../../arch/i686/hal/memory/memory.c"
#include "../../../../utils/kernel_utils.c"
#include "../../vbe.h"

typedef struct Window {
  int32_t x, y;      // x,y coordinates of top left corner
  u32 width, height; // width and height of the window
  u32 zIndex;
  u32 *windowFb;

  struct Window *next;
} Window;

// Circular Linked List of windows,
// Win1 -> Win2 -> Win3 -> Win4
// windows have SUB nodes which denote dialogs/popups which are RELATIVE to the
// parent's position(?) order by Z-Index

//      Layer             Window
//        1                 BG
//        2                 System Panel (Taskbar and toolbar)
//        3                 Applications and Dialogues
//        4                 Tooltips and cursor

typedef struct {
  Window *Background, *SystemPanel, *Applications, *Tooltips;
} SceneGraph;

void traverseSceneGraph(SceneGraph *sg, VbeDriverState *vbe);
void renderLayer(Window *layer, VbeDriverState *vbe);
SceneGraph *SceneGraphInit();
void renderWindow(Window *window, VbeDriverState *VbeDriver);