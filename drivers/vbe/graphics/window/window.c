#include "./window.h"
#include "../../../../meta/framebuffer/images/a.c"

void renderWindow(Window *window, u32 *bf, u32 w) {
  u32 *t = window->windowFb;
  for (int i = 0; i < window->height; i++) {
    u32 *start = bf + w * (i + window->y) + window->x;
    memcpy(start, t, window->width);
    t += window->width * sizeof(u32);
  }
}