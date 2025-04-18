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
  terminal_color = vga_entry_color(WHITE, BLACK);
  // VbeDriver.renderLoop();
  int *arr = kmalloc(sizeof(int) * 10);
  bool res = true;
  for (int i = 0; i < 10; i++) {
    arr[i] = i;
    res &= arr[i] == i;
  }
  kfree(arr);
  for (int i = 0; i < 10; i++) {
    res &= arr[i] == 0;
  }
  assert(res, "kfree and kmalloc are working properly");
  printf("done");
  killQemu();
  for (;;)
    asm("hlt");
}