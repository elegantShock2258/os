#include "./tests/testing.c"
#include "arch/i686/hal/interrupts/pit/pit.c"
#include "arch/i686/hal/io/printf.c"
#include "arch/i686/hal/io/printf.h"
#include "arch/i686/hal/io/stdio.c"
#include "arch/i686/hal/memory/kheap/kheap.c"
#include "drivers/vbe/graphics/window/window.h"
#include "drivers/vbe/vbe.c"
#include "utils/kernel_utils.c"

void main(void) {
  VbeDriver.renderLoop();
  for (;;)
    asm("hlt");
}