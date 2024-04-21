#pragma once
#include "vbe.h"
#include "../../../../multiboot.h"
#include "../../utils/kernel_utils.c"
#include "../hal.h"
#include "../io/printf.c"
#include <stdint.h>
typedef struct {
  char VbeSignature[4];     // == "VESA"
  uint16_t VbeVersion;      // == 0x0300 for VBE 3.0
  uint16_t OemStringPtr[2]; // isa vbeFarPtr
  uint8_t Capabilities[4];
  uint16_t VideoModePtr[2]; // isa vbeFarPtr
  uint16_t TotalMemory;     // as # of 64KB blocks
  uint8_t _Reserved[492];
} VbeInfoBlock __attribute__((packed));

typedef struct {
  uint16_t
      attributes; // deprecated, only bit 7 should be of interest to you, and it
                  // indicates the mode supports a linear frame buffer.
  uint8_t window_a;     // deprecated
  uint8_t window_b;     // deprecated
  uint16_t granularity; // deprecated; used while calculating bank numbers
  uint16_t window_size;
  uint16_t segment_a;
  uint16_t segment_b;
  uint32_t win_func_ptr; // deprecated; used to switch banks from protected mode
                         // without returning to real mode
  uint16_t pitch;        // number of bytes per horizontal line
  uint16_t width;        // width in pixels
  uint16_t height;       // height in pixels
  uint8_t w_char;        // unused...
  uint8_t y_char;        // ...
  uint8_t planes;
  uint8_t bpp;   // bits per pixel in this mode
  uint8_t banks; // deprecated; total number of banks in this mode
  uint8_t memory_model;
  uint8_t bank_size; // deprecated; size of a bank, almost always 64 KB but may
                     // be 16 KB...
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

  uint32_t framebuffer; // physical address of the linear frame buffer; write
                        // here to draw to the screen
  uint32_t off_screen_mem_off;
  uint16_t off_screen_mem_size; // size of memory in the framebuffer but not
                                // being displayed on the screen
  uint8_t reserved1[206];
} vbe_mode_info_structure __attribute__((packed));

/*TODO: look at diff b/w vbe_mode_info_structure and svga_mode_info_t, is it
the same? or is it different like vbe and framebuffer_rb? */
vbe_mode_info_structure *vbe_info_block;
VbeInfoBlock *vbe_control_block;
uint32_t *fb;

int vbe_h;
int vbe_w;
int bpp;

void drawShit(vbe_mode_info_structure* info, uint32_t *fb) {
  for (int y = 0; y < info->width; y++) {
    for (int x = 0; x < info->height; x++) {
      fb[y * info->pitch + x] = x+y;
    }
  }
}
void vbe_info(multiboot_info_t *multiboot_grub_info) {
  vbe_control_block = (VbeInfoBlock *)multiboot_grub_info->vbe_control_info;
  vbe_info_block =
      (vbe_mode_info_structure *)multiboot_grub_info->vbe_mode_info;

  vbe_h = vbe_info_block->height;
  vbe_w = vbe_info_block->width;
  bpp = vbe_info_block->bpp;
  fb = (uint32_t *)multiboot_grub_info->framebuffer_addr;

  drawShit(vbe_info_block, fb);
}
