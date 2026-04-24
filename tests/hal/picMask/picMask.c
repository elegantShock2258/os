#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/interrupts/pic/pic.c"
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

  // mask IRQ 3 (COM2) — should not affect test flow
  PIC_Mask(3);
  // read PIC1 data port to verify bit 3 is set
  u8 mask = inb(0x21);
  res = res && ((mask & (1 << 3)) != 0);

  // unmask IRQ 3
  PIC_Unmask(3);
  mask = inb(0x21);
  res = res && ((mask & (1 << 3)) == 0);

  // mask IRQ 10 (PIC2, IRQ 2 on slave)
  PIC_Mask(10);
  u8 mask2 = inb(0xA1);
  res = res && ((mask2 & (1 << 2)) != 0);

  // unmask IRQ 10
  PIC_Unmask(10);
  mask2 = inb(0xA1);
  res = res && ((mask2 & (1 << 2)) == 0);

  assert(res, "PIC mask/unmask working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
