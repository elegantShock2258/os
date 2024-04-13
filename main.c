#include "arch/i686/io/printf.h"
#include "arch/i686/io/stdio.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  char buffer[100];
  gets(buffer, 10);
  printf("%s", buffer);

  for (;;)
    asm("hlt");
}
