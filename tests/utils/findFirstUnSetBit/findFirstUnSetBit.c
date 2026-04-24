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

  // all bits set -> should return -1
  res = res && (findFirstUnSetBit(0xFFFFFFFF) == -1);

  // zero -> first unset bit from MSB side
  int pos = findFirstUnSetBit(0);
  res = res && (pos >= 0);

  // 0x7FFFFFFF -> bit 31 is unset
  int pos2 = findFirstUnSetBit(0x7FFFFFFF);
  res = res && (pos2 >= 0);

  assert(res, "findFirstUnSetBit working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
