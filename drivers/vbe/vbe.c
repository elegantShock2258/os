#pragma once
#include "vbe.h"

int _VBE_renderGUI = 1;

VbeDriverState VbeDriver;

static inline void _VBE_putpixel(int x, int y, int color) {
  if (x >= 0 && x < VbeDriver.vbe_w && y >= 0 && y < VbeDriver.vbe_h) {
    VbeDriver.fb[(y * VbeDriver.pitch) / VbeDriver.colorDepth + x] = color;
  }
}

void _VBE_putcursor(int x, int y) {
  for (int dy = 0; dy < CURSOR_HEIGHT; dy++) {
    for (int dx = 0; dx < CURSOR_WIDTH; dx++) {
      _VBE_putpixel(x + dx, y + dy, COLOR(0, 0, 0));
    }
  }
}

void _VBE_fillScreen(int color) {
  for (int y = 0; y < VbeDriver.vbe_h; y++) {
    for (int x = 0; x < VbeDriver.vbe_w; x++) {
      _VBE_putpixel(x, y, color);
    }
  }
}
void _VBE_drawRect(int x, int y, int w, int h, int color){
  // draw a rectangle!
  for (int dy = y; dy < y + h; dy++) {
    for (int dx = x; dx < x + w; dx++) {
      _VBE_putpixel(dx, dy, color);
    }
  }
}
void _VBE_init(int ebx) {
  multiboot_info_t *multiboot_grub_info = (multiboot_info_t *)ebx;
  VbeDriver.vbe_control_block =
      (VbeInfoBlock *)multiboot_grub_info->vbe_control_info;
  VbeDriver.vbe_info_block =
      (vbe_mode_info_structure *)multiboot_grub_info->vbe_mode_info;

  VbeDriver.pitch = VbeDriver.vbe_info_block->pitch;
  VbeDriver.vbe_w = VbeDriver.vbe_info_block->width;
  VbeDriver.vbe_h = VbeDriver.vbe_info_block->height;
  VbeDriver.bpp = VbeDriver.vbe_info_block->bpp;
  VbeDriver.fb = (uint32_t *)VbeDriver.vbe_info_block->framebuffer;

  // FIXME: BACKBUFFER ERROR ON EACH RENDER
  // VbeDriver.bf = (uint32_t *)kmalloc(sizeof(uint32_t) * VbeDriver.vbe_h * VbeDriver.vbe_w);
  // if (!VbeDriver.bf) {
  //   printf("Failed to allocate backbuffer.\n");
  // }
}

void _VBE_wait(int milliseconds) {
  for (volatile int i = 0; i < milliseconds * 100000; i++)
    ;
}

void _VBE_render() {
  _VBE_fillScreen(COLOR(255, 0, 0)); // Red
  _VBE_putcursor(MouseDriver.mouse_x, MouseDriver.mouse_y);
  // _VBE_drawRect(10,10,100,100,COLOR(0,255,0));
}
void _VBE_renderLoop() {
  // DONT re-render every loop?
  // only update dirty pixels
  //
  while (1) {
    _VBE_render();
    sleep(1000);
  }
}

void VbeConstructor(int ebx) {
  VbeDriver.renderGUI = _VBE_renderGUI;
  VbeDriver.colorDepth = 4;

  VbeDriver.putpixel = _VBE_putpixel;
  VbeDriver.putcursor = _VBE_putcursor;
  VbeDriver.fillScreen = _VBE_fillScreen;
  VbeDriver.wait = _VBE_wait;
  VbeDriver.render = _VBE_render;
  VbeDriver.renderLoop = _VBE_renderLoop;
  VbeDriver.init = _VBE_init;

  VbeDriver.Constructor = VbeConstructor;

  _VBE_init(ebx);
}
