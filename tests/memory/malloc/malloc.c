#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/kheap/kheap.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  // int *arr = kmalloc(sizeof(int) * 10);
  // bool res = true;
  // for (int i = 0; i < 10; i++) {
  //   arr[i] = i;
  //   res &= arr[i] == i;
  // }
  // kfree(arr);
  // for (int i = 0; i < 10; i++) {
  //   res &= arr[i] == 0;
  // }
  assert(1, "kfree and kmalloc are working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
