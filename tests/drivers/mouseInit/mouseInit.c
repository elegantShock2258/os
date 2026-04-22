#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/memory.c"
#include "../../../drivers/mouse/mouse.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;

  // MouseConstructor() was called in drivers_init()
  // verify function pointers are set
  res = res && (MouseDriver.mouse_wait != NULL);
  res = res && (MouseDriver.mouse_write != NULL);
  res = res && (MouseDriver.mouse_read != NULL);
  res = res && (MouseDriver.mouse != NULL);
  res = res && (MouseDriver.mouse_install != NULL);
  res = res && (MouseDriver.Constructor != NULL);

  // verify initial mouse position is (0, 0)
  res = res && (MouseDriver.mouse_x == 0);
  res = res && (MouseDriver.mouse_y == 0);

  // verify initial cycle is 0
  res = res && (MouseDriver.mouse_cycle == 0);

  // verify packet magic is not set initially (no mouse events yet)
  res = res && (MouseDriver.packet.magic != 0xDEAD);

  assert(res, "mouse init and state working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
