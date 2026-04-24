#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/memory.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;
  res = res && (popcount(0) == 0);
  res = res && (popcount(1) == 1);
  res = res && (popcount(0xFF) == 8);
  res = res && (popcount(0xF0F0F0F0) == 16);
  res = res && (popcount(0xFFFFFFFF) == 32);
  res = res && (popcount(0x80000000) == 1);
  assert(res, "popcount working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
