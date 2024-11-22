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
  int src[10];
  bool res = true;
  memset(src, 10, 10);
  for (int i = 0; i < 10; i++){
    res = res && (src[i] == 10);
    printf("Element at index %d: %d\n", i, src[i]);
  }
  assert(res, "memset working properly");
  // VbeDriver.renderLoop();
  killQemu();
  for (;;)
    asm("hlt");
}
