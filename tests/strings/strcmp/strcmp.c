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

  // equal strings
  res = res && (strcmp("hello", "hello") == 0);

  // different strings
  res = res && (strcmp("hello", "world") != 0);

  // empty strings
  res = res && (strcmp("", "") == 0);

  // prefix mismatch
  res = res && (strcmp("abc", "abd") != 0);

  // different lengths
  res = res && (strcmp("ab", "abc") != 0);

  assert(res, "strcmp working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
