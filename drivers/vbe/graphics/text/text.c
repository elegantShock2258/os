#pragma once
#include "text.h"
#include "../../../../utils/kernel_utils.c"

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

void renderText(int x, int y, int width, int height, char *text, int color,
                int scale, enum TextOverFlow overFlow) {
  u32 textWidth = strlen(text) * 8 * scale;
  if ((x + textWidth) >=)
    for (int i = 0; text[i] != '\0'; i++) {
      renderChar(x, y, scale, color, text[i]);
      // TODO: text wrap and text ellipses and text overflow
      x += 8 * scale;
    }
}