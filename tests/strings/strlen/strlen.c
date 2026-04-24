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

  res = res && (strlen("hello") == 5);
  res = res && (strlen("") == 0);
  res = res && (strlen("a") == 1);
  res = res && (strlen("hello world") == 11);

  assert(res, "strlen working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
