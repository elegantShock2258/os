#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/interrupts/pit/pit.c"
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

  // irq_init() registered timer on IRQ0 and started PIT at 1000 Hz
  // ticks should be 0 or very small right now
  u32 startTicks = ticks;

  // sleep for ~50ms — PIT should fire ~50 times
  sleep(50);

  // ticks should have increased
  res = res && (ticks > startTicks);
  res = res && ((ticks - startTicks) >= 10); // at least 10 ticks in 50ms

  // verify IRQ0 handler is registered
  res = res && (g_IRQHandlers[0] != NULL);

  assert(res, "IRQ PIT timer ticking properly");
  killQemu();
  for (;;)
    asm("hlt");
}
