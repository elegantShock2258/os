#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/memory.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"
#include <cassert>

void main(void) {

  printf("hi\n");
  u32 old = ticks;
  sleep(5000);
  u32 new = ticks;
  printf("bye\n");
  bool eq = (new - old) == 5000;
  assert(eq,"sleep() working");
  // VbeDriver.renderLoop();
  killQemu();
  for (;;)
    asm("hlt");
}
