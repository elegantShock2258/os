#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/kheap/kheap.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  char y = getc();
  printf("%c", y);

  int *arr = kmalloc(sizeof(int) * 10);
  for (int i = 0; i < 10; i++) {
    arr[i] = i;
  }
  for (int i = 0; i < 10; i++) {
    printf("Element at index %d: %d\n", i, arr[i]);
  }
  kfree(arr);
  for (int i = 0; i < 10; i++) {
    printf("Element at index %d: %d\n", i, arr[i]);
  }
  // VbeDriver.renderLoop();
  for (;;)
    asm("hlt");
}
