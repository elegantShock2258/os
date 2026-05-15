#pragma once
#include "../../../../utils/ds/AvlTree/AvlTree.c"
#include "../window/window.c"

extern Node WindowRoot;
void uiInit() {
  // this is the front screen ui

  // add a tool bar at the top

  Window *toolBar = kmalloc(sizeof(Window));
  toolBar->x = 0;
  toolBar->y = 0;
  toolBar->width = 1920;
  toolBar->height = 40;
  toolBar->windowFb =
      kmalloc((toolBar->width) * (toolBar->height) * sizeof(u32));
  for (u32 i = 0; i < toolBar->width * toolBar->height; i++) {
    toolBar->windowFb[i] =
        COLOR(255, 0, 0); // Ensure all pixels are properly set
  }

  toolBar->zIndex = 3;
  Node *res = insert(&WindowRoot, toolBar, &(toolBar->zIndex));

  Window *toolBar2 = kmalloc(sizeof(Window));
  toolBar2->x = 0;
  toolBar2->y = 0;
  toolBar2->width = 190;
  toolBar2->height = 40;
  toolBar2->windowFb =
      kmalloc((toolBar2->width) * (toolBar2->height) * sizeof(u32));
  for (u32 i = 0; i < toolBar2->width * toolBar2->height; i++) {
    toolBar2->windowFb[i] =
        COLOR(255, 233, 0); // Ensure all pixels are properly set
  }

  toolBar2->zIndex = 4;

  insert(&WindowRoot, toolBar2, &(toolBar2->zIndex));
}