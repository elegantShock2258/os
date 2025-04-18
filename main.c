#include "./tests/testing.c"
#include "arch/i686/hal/interrupts/pit/pit.c"
#include "arch/i686/hal/io/printf.c"
#include "arch/i686/hal/io/printf.h"
#include "arch/i686/hal/io/stdio.c"
#include "arch/i686/hal/memory/kheap/kheap.c"
#include "drivers/vbe/graphics/window/window.h"
#include "drivers/vbe/vbe.c"
#include "utils/kernel_utils.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  // VbeDriver.renderLoop();
  int src[10], dst[10];
  for (int i = 0; i < 10; i++) {
    src[i] = i;
  }
  bool res = true;
  memcpy(src, dst, 10);
  for (int i = 0; i < 10; i++)
    res = res && (src[i] == dst[i]);
  assert(res, "memcpy working properly");
  printf("%d", res);
  for (;;)
    asm("hlt");
}