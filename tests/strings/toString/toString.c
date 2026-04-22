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
  char buf[64];

  // base 10 positive
  to_string(123, buf, 10);
  res = res && (strcmp(buf, "123") == 0);

  // base 10 zero
  to_string(0, buf, 10);
  res = res && (strcmp(buf, "0") == 0);

  // base 10 negative
  to_string(-42, buf, 10);
  res = res && (strcmp(buf, "-42") == 0);

  // base 16
  to_string(255, buf, 16);
  res = res && (strcmp(buf, "ff") == 0);

  // base 2
  to_string(10, buf, 2);
  res = res && (strcmp(buf, "1010") == 0);

  assert(res, "to_string working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
