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

  // test getNthBit
  u32 val = 0xA5; // 10100101
  res = res && (getNthBit(val, 0) == true);
  res = res && (getNthBit(val, 1) == false);
  res = res && (getNthBit(val, 2) == true);
  res = res && (getNthBit(val, 7) == true);

  // test setNthBit: set bit 1, then verify
  u32 data = 0;
  setNthBit(&data, 5, true);
  res = res && (getNthBit(data, 5) == true);
  res = res && (data == (1 << 5));

  // test setNthBit: clear bit
  setNthBit(&data, 5, false);
  res = res && (getNthBit(data, 5) == false);
  res = res && (data == 0);

  assert(res, "getNthBit and setNthBit working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
