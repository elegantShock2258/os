#include "arch/i686/io/stdio.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  unsigned char c = getc();
  printf("bro getc got: %c\n",c);
  for (;;)
    asm("hlt");
}
