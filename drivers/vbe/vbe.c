#pragma once
#include "vbe.h"

int renderGUI = 1;
#define COLOR(r, g, b) ((b) | (g << 8) | (r << 16))

vbe_mode_info_structure *vbe_info_block;
VbeInfoBlock *vbe_control_block;

uint32_t *fb, *bf;

int vbe_h;
int vbe_w;
int bpp;
int pitch;
int colorDepth = 4;

static inline void putpixel(int x, int y, int color) {
  if (x >= 0 && x < vbe_w && y >= 0 && y < vbe_h) {
    fb[(y * pitch) / colorDepth + x] = color;
  }
}
#define CURSOR_WIDTH 30
#define CURSOR_HEIGHT 30
#define CURSOR_COLOR COLOR(255, 255, 255)

void putcursor(int x, int y) {
  for (int dy = 0; dy < CURSOR_HEIGHT; dy++) {
    for (int dx = 0; dx < CURSOR_WIDTH; dx++) {
      putpixel(x + dx, y + dy, COLOR(x%255, y%255, (dy + dx)%255));
    }
  }
}

void fillScreen(int color) {
  for (int y = 0; y < vbe_h; y++) {
    for (int x = 0; x < vbe_w; x++) {
      putpixel(x, y, color);
    }
  }
}

vbe_mode_info_structure *vbe_info(multiboot_info_t *multiboot_grub_info) {
  vbe_control_block = (VbeInfoBlock *)multiboot_grub_info->vbe_control_info;
  vbe_info_block =
      (vbe_mode_info_structure *)multiboot_grub_info->vbe_mode_info;

  pitch = vbe_info_block->pitch;
  vbe_w = vbe_info_block->width;
  vbe_h = vbe_info_block->height;
  bpp = vbe_info_block->bpp;
  fb = (uint32_t *)vbe_info_block->framebuffer;

  //FIXME: BACKBUFFER ERROR ON EACH RENDER
  bf = (uint32_t *)kmalloc(sizeof(uint32_t) * vbe_h * vbe_w);
  if (!bf) {
    printf("Failed to allocate backbuffer.\n");
    return NULL;
  }

  return vbe_info_block;
}

void wait(int milliseconds) {
  for (volatile int i = 0; i < milliseconds * 100000; i++)
    ;
}
int x = 0, y = 0;
void render() {
  if (KeyboardDriverState->keyboard_irq_handled) {
    fillScreen(COLOR(255, 0, 0)); // Red
    printf("Rendering red screen\n");
  } else {
    fillScreen(COLOR(0, 0, 255)); // Blue
    printf("Rendering blue screen\n");
  }
  x += mb.xSign * mouse_byte[1];
  y += mb.ySign * mouse_byte[2];
  putcursor(mouse_x, mouse_y);
}
void renderLoop() {
  while (1) {
    render();
    wait(60);
  }
}