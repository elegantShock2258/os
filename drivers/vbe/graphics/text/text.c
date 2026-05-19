#pragma once
#include "text.h"

void renderChar(int x, int y, int scale, int color, char c) {
  char *bitmap = font8x8_basic[c - '\0'];
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      bool isPixelSet = bitmap[i] & (1 << j);
      if (isPixelSet) {
        VbeDriver.drawRect(x + j * scale, y + i * scale, scale, scale, color);
      }
    }
  }
}
void renderText(int x, int y, char *text, int color, int scale) {
  u32 *start = VbeDriver.bf + (y * VbeDriver.vbe_w) + x;

  //

  // { 0x0C, 0x1E, 0x33, 0x33, 0x3F, 0x33, 0x33, 0x00},   // U+0041 (A)
  // 00001100
  // 00011110
  // 00110011
  // 00110011
  // 00111111
  // 00110011
  // 00110011
  // 00000000
  for (int i = 0; text[i] != '\0'; i++) {
    renderChar(x, y, scale, color, text[i]);
    // TODO: text wrap and text ellipses and text overflow
    x += 8 * scale;
  }
}