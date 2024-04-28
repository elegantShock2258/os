#include "arch/i686/hal/io/printf.c"
#include "arch/i686/hal/io/printf.h"
#include "arch/i686/hal/io/stdio.c"
#include "arch/i686/hal/kheap/kheap.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  int * y = (int*)kmalloc(10*sizeof(int));
  for(int i = 0; i < 10; i++) 
    y[i] = i;
  for(int i = 0; i < 10; i++) 
    printf("%d", y[i]);
  
  for (;;)
    asm("hlt");
}
