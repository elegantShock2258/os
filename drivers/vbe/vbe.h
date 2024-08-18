#pragma once
#include "../../utils/kernel_utils.c"

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



typedef struct svga_mode_info {
	uint16_t attributes;
	uint8_t windowA, windowB;
	uint16_t granularity;
	uint16_t windowSize;
	uint16_t segmentA, segmentB;
	uint32_t winFuncPtr; // ptr to INT 0x10 Function 0x4F05
	uint16_t pitch; // bytes per scan line

	uint16_t screen_width, screen_height; // resolution
	uint8_t wChar, yChar, planes, bpp, banks; // number of banks
	uint8_t memoryModel, bankSize, imagePages;
	uint8_t reserved0;

	// color masks
	uint8_t readMask, redPosition;
	uint8_t greenMask, greenPosition; 
	uint8_t blueMask, bluePosition;
	uint8_t reservedMask, reservedPosition;
	uint8_t directColorAttributes;

	uint32_t physbase; //pointer to LFB in LFB modes 
	uint32_t offScreenMemOff;
	uint16_t offScreenMemSize;
	uint8_t reserved1[206];
} __attribute__((packed)) svga_mode_info_t;

