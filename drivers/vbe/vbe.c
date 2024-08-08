#pragma once
#include "vbe.h"
#include "../../arch/i686/hal/hal.h"
#include "../../arch/i686/hal/interrupts/pit/pit.c"
#include "../../arch/i686/hal/io/printf.c"
#include "../../arch/i686/hal/memory/kheap/kheap.c"
#include "../../arch/i686/hal/memory/memory.c"
#include "../../arch/i686/hal/paging/paging.c"
#include "../../multiboot.h"
#include "../../utils/kernel_utils.c"
#include "../keyboard/keyboard.c"
#include "../mouse/mouse.c"

int renderGUI = 1;
#define COLOR(r, g, b) ((b) | (g << 8) | (r << 16))

typedef struct {
  char VbeSignature[4];
  uint16_t VbeVersion;
  uint16_t OemStringPtr[2];
  uint8_t Capabilities[4];
  uint16_t VideoModePtr[2];
  uint16_t TotalMemory;
  uint8_t _Reserved[492];
} VbeInfoBlock __attribute__((packed));

typedef struct {
  uint16_t attributes;
  uint8_t window_a;
  uint8_t window_b;
  uint16_t granularity;
  uint16_t window_size;
  uint16_t segment_a;
  uint16_t segment_b;
  uint32_t win_func_ptr;
  uint16_t pitch;
  uint16_t width;
  uint16_t height;
  uint8_t w_char;
  uint8_t y_char;
  uint8_t planes;
  uint8_t bpp;
  uint8_t banks;
  uint8_t memory_model;
  uint8_t bank_size;
  uint8_t image_pages;
  uint8_t reserved0;
  uint8_t red_mask;
  uint8_t red_position;
  uint8_t green_mask;
  uint8_t green_position;
  uint8_t blue_mask;
  uint8_t blue_position;
  uint8_t reserved_mask;
  uint8_t reserved_position;
  uint8_t direct_color_attributes;
  uint32_t *framebuffer;
  uint32_t off_screen_mem_off;
  uint16_t off_screen_mem_size;
  uint8_t reserved1[206];
} vbe_mode_info_structure __attribute__((packed));

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
  // Draw a rectangular cursor at position (x, y)
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

  // FIXME: BACKBUFFER ERROR ON EACH RENDER
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
  // if (keyboard_irq_handled) {
  //   fillScreen(COLOR(255, 0, 0)); // Red
  //   printf("Rendering red screen\n");
  // } else {
  //   fillScreen(COLOR(0, 0, 255)); // Blue
  //   printf("Rendering blue screen\n");
  // }
  x += mb.xSign * mouse_byte[1];
  y += mb.ySign * mouse_byte[2];
  putcursor(mouse_x, mouse_y);
}
void renderLoop() {
  while (1) {
    render();
  }
}
