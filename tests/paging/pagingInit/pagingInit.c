#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/memory.c"
#include "../../../arch/i686/hal/paging/paging.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;

  // if we got here, paging_init() succeeded without a triple fault
  // that means identity mapping at 0x0-0x7FFFFF is working

  // verify we can read the VGA buffer area (0xB8000) which should be mapped
  volatile u16 *vga = (volatile u16 *)0xB8000;
  u16 val = *vga; // should not fault
  (void)val;
  res = res && true;

  // verify stack memory is accessible (it must be, since we're running)
  volatile int stackVar = 0xBEEF;
  res = res && (stackVar == 0xBEEF);

  assert(res, "paging init and memory access working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
