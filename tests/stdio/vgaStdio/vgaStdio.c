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

  // test vga_entry_color produces a valid color byte
  uint8_t color = vga_entry_color(WHITE, BLACK);
  res = res && (color == (BLACK << 4 | WHITE));

  // test vga_entry packs char + color correctly
  uint16_t entry = vga_entry('A', color);
  res = res && ((entry & 0xFF) == 'A');
  res = res && (((entry >> 8) & 0xFF) == color);

  // test putchr/getchr round-trip on VGA buffer
  putchr(0, 0, 'X', color);
  char got = getchr(0, 0);
  res = res && (got == 'X');

  // test to_string via stdio
  char buf[32];
  to_string(42, buf, 10);
  res = res && (strcmp(buf, "42") == 0);

  to_string(255, buf, 16);
  res = res && (strcmp(buf, "ff") == 0);

  assert(res, "VGA stdio working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
