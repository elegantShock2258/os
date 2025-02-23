#pragma once
#include "vbe.h"
#include "../../arch/i686/hal/io/stdio.c"
#include "../../tests/testing.c"
#include "graphics/colors/colors.h"
#include "graphics/window/window.h"

int _VBE_renderGUI = 1;

VbeDriverState VbeDriver;

char *vbeDriverStateToJson(VbeDriverState *state) {
  char json_str[1024];

  // Constructing JSON string
  snprintf(
      json_str, 1024,
      "{\n"
      "  \"renderGUI\": %d,\n"
      "  \"vbe_info_block\": {\n"
      "    \"VbeSignature\": \"%s\",\n"
      "    \"VbeVersion\": %u,\n"
      "    \"TotalMemory\": %u\n"
      "  },\n"
      "  \"vbe_control_block\": {\n"
      "    \"attributes\": %u,\n"
      "    \"window_a\": %u,\n"
      "    \"window_b\": %u,\n"
      "    \"granularity\": %u,\n"
      "    \"window_size\": %u,\n"
      "    \"segment_a\": %u,\n"
      "    \"segment_b\": %u,\n"
      "    \"win_func_ptr\": %u,\n"
      "    \"pitch\": %u,\n"
      "    \"width\": %u,\n"
      "    \"height\": %u,\n"
      "    \"w_char\": %u,\n"
      "    \"y_char\": %u,\n"
      "    \"planes\": %u,\n"
      "    \"bpp\": %u,\n"
      "    \"banks\": %u,\n"
      "    \"memory_model\": %u,\n"
      "    \"bank_size\": %u,\n"
      "    \"image_pages\": %u,\n"
      "    \"red_mask\": %u,\n"
      "    \"red_position\": %u,\n"
      "    \"green_mask\": %u,\n"
      "    \"green_position\": %u,\n"
      "    \"blue_mask\": %u,\n"
      "    \"blue_position\": %u,\n"
      "    \"reserved_mask\": %u,\n"
      "    \"reserved_position\": %u,\n"
      "    \"direct_color_attributes\": %u,\n"
      "    \"framebuffer\": \"%p\",\n"
      "    \"off_screen_mem_off\": %u,\n"
      "    \"off_screen_mem_size\": %u\n"
      "  },\n"
      "  \"vbe_h\": %d,\n"
      "  \"vbe_w\": %d,\n"
      "  \"bpp\": %d,\n"
      "  \"pitch\": %d,\n"
      "  \"colorDepth\": %d\n"
      "}",
      state->renderGUI, state->vbe_control_block->VbeSignature,
      state->vbe_control_block->VbeVersion,
      state->vbe_control_block->TotalMemory, state->vbe_info_block->attributes,
      state->vbe_info_block->window_a, state->vbe_info_block->window_b,
      state->vbe_info_block->granularity, state->vbe_info_block->window_size,
      state->vbe_info_block->segment_a, state->vbe_info_block->segment_b,
      state->vbe_info_block->win_func_ptr, state->vbe_info_block->pitch,
      state->vbe_info_block->width, state->vbe_info_block->height,
      state->vbe_info_block->w_char, state->vbe_info_block->y_char,
      state->vbe_info_block->planes, state->vbe_info_block->bpp,
      state->vbe_info_block->banks, state->vbe_info_block->memory_model,
      state->vbe_info_block->bank_size, state->vbe_info_block->image_pages,
      state->vbe_info_block->red_mask, state->vbe_info_block->red_position,
      state->vbe_info_block->green_mask, state->vbe_info_block->green_position,
      state->vbe_info_block->blue_mask, state->vbe_info_block->blue_position,
      state->vbe_info_block->reserved_mask,
      state->vbe_info_block->reserved_position,
      state->vbe_info_block->direct_color_attributes,
      state->vbe_info_block->framebuffer,
      state->vbe_info_block->off_screen_mem_off,
      state->vbe_info_block->off_screen_mem_size, state->vbe_h, state->vbe_w,
      state->bpp, state->pitch, state->colorDepth);

  outputMessage(json_str);
  return NULL;
}

static inline void _VBE_putpixel(int x, int y, int color) {
  if (x >= 0 && x < VbeDriver.vbe_w && y >= 0 && y < VbeDriver.vbe_h) {
    VbeDriver.bf[(y * VbeDriver.pitch) / VbeDriver.colorDepth + x] = color;
  }
}

void _VBE_drawRect(int x, int y, int width, int height, int color) {
  for (u32 row = y; row < y + height; row++) {
    u32 *row_start = VbeDriver.bf + (row * VbeDriver.vbe_w) + x;

    __asm__(
        "movl %[width], %%ecx \n"     // Set ECX to the number of pixels per row
        "movl %[color], %%eax \n"     // Set EAX to the color
        "movl %[row_start], %%edi \n" // Set EDI to the start of the current row
        "rep stosl \n"                // Repeat storing the color into memory
        :
        : [width] "r"(width), [color] "r"(color), [row_start] "r"(row_start)
        : "%ecx", "%eax", "%edi" // Clobbered registers
    );
  }
}

void _VBE_putcursor(int x, int y) {
  _VBE_drawRect(x, y, CURSOR_WIDTH, CURSOR_HEIGHT, COLOR(0, 0, 0));
}

void _VBE_fillScreen(int color) {
  _VBE_drawRect(0, 0, VbeDriver.vbe_w, VbeDriver.vbe_h, color);
}
void exportVBE() { vbeDriverStateToJson(&VbeDriver); }

Window *w;
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
  VbeDriver.bf = (uint32_t *)kmalloc_primitive(
      sizeof(uint32_t) * VbeDriver.vbe_h * VbeDriver.vbe_w);
  if (!VbeDriver.bf) {
    printf("Failed to allocate backbuffer.\n");
  }
  w = kmalloc(sizeof(Window));
  w->x = 20;
  w->y = 20;
  w->width = 100;
  w->height = 100;
  w->windowFb = kmalloc(sizeof(u32) * w->width * w->height);

  exportVBE();
}

void _VBE_render() {
  _VBE_fillScreen(COLOR(255, 0, 0));
  _VBE_drawRect(10, 10, 100, 100, COLOR(255, 255, 255));
}
void _VBE_renderLoop() {
  // DONT re-render every loop?
  // only update dirty pixels
  while (1) {
    // _VBE_render();
    for (int i = 0; i < 1080; i++) {
      for (int j = 0; j < 1920; j++)
        VbeDriver.bf[i * 1920 + j] = COLOR(
            image_data[i][j][0], image_data[i][j][1], image_data[i][j][2]);
    }

    _VBE_putcursor(MouseDriver.mouse_x, MouseDriver.mouse_y);

    // memset(w->windowFb, COLOR(0, 0, 0), sizeof(u32) * w->width * w->height);
    // renderWindow(NULL, VbeDriver.bf, VbeDriver.vbe_w);

    memcpy(VbeDriver.fb, VbeDriver.bf, VbeDriver.vbe_h * VbeDriver.vbe_w);
    sleep(100); // somehow gui doesnt update without this
  }
}

void VbeConstructor(int ebx) {
  VbeDriver.renderGUI = _VBE_renderGUI;
  VbeDriver.colorDepth = 4;

  VbeDriver.putpixel = _VBE_putpixel;
  VbeDriver.putcursor = _VBE_putcursor;
  VbeDriver.fillScreen = _VBE_fillScreen;
  VbeDriver.render = _VBE_render;
  VbeDriver.renderLoop = _VBE_renderLoop;
  VbeDriver.init = _VBE_init;

  VbeDriver.Constructor = VbeConstructor;

  _VBE_init(ebx);
}
