#include "arch/i686/hal/interrupts/irq/irq.c"
#include "arch/i686/hal/io/printf.c"
#include "arch/i686/hal/io/printf.h"
#include "arch/i686/hal/io/stdio.c"
#include "arch/i686/hal/memory/kheap/kheap.c"
#include "drivers/vbe/vbe.c"
#include "utils/kernel_utils.c"

void main(void) {

  terminal_color = vga_entry_color(WHITE, BLACK);
  VbeDriver.renderLoop();
  for (;;)
    asm("hlt");
}
