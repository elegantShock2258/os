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
  int src[10] = {0}, dst[10] = {0};
  bool eq = memcmp(src, dst, 10);
  for(int i = 0;i<10;i++){
    printf(" %d %d ",src[i],dst[i]);
  }
  assert(!eq, "memcmp working properly");
  // VbeDriver.renderLoop();
  killQemu();
  for (;;)
    asm("hlt");
}

