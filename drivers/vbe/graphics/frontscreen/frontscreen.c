#pragma once
#include "../window/window.h"

void uiInit(SceneGraph *sg) {
  // this is the front screen ui
  Window *bg = kmalloc(sizeof(Window));
  bg->x = 0;
  bg->y = 0;
  // FIXME: should be VBEDriver.vbe_w,vbe_h
  bg->width = 1920;
  bg->height = 1080;
  bg->windowFb = kmalloc((bg->width) * (bg->height) * sizeof(u32));
  for (u32 i = 0; i < bg->width * bg->height; i++) {
    bg->windowFb[i] = COLOR(255, 255, 255);
  }

  bg->zIndex = 1;
  bg->next = NULL;
  sg->Background = bg;

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

  toolBar->next = toolBar2;
  toolBar2->next = NULL;

  sg->SystemPanel = toolBar;
}