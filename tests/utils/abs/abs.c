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
  res = res && (abs(5) == 5);
  res = res && (abs(-5) == 5);
  res = res && (abs(0) == 0);
  res = res && (abs(-1) == 1);
  res = res && (abs(2147483) == 2147483);
  assert(res, "abs working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
