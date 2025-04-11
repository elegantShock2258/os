#include "./tests/testing.c"
#include "arch/i686/hal/interrupts/pit/pit.c"
#include "arch/i686/hal/io/printf.c"
#include "arch/i686/hal/io/printf.h"
#include "arch/i686/hal/io/stdio.c"
#include "arch/i686/hal/memory/kheap/kheap.c"
#include "drivers/vbe/vbe.c"
#include "utils/kernel_utils.c"

void main(void) {

  terminal_color = vga_entry_color(WHITE, BLACK);

  int *arr = kmalloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    arr[i] = i;
  }
  for (int i = 0; i < 10; i++) {
    printf(" %d: %d ", i, arr[i]);
  }
  printf("\n");
  kfree(arr);
  for (int i = 0; i < 10; i++) {
    logf("hi %d", i);
    printf(" %d: %d ", i, arr[i]);
  }
  // outputQemuMessage("hfjkhjkjh");
  // printFramebuffer(VbeDriver.fb, VbeDriver.vbe_h, VbeDriver.vbe_w, "VESA
  // FB"); VbeDriver.renderLoop();
  for (;;)
    asm("hlt");
}
