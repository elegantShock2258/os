#include "arch/i686/io/printf.h"
#include "arch/i686/io/stdio.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  char name[21000];
  
  char t = getc();

  printf("%c %u\n", (t),t);
  t = getc();
  printf("%c %u\n", (t),t);
  t = getc();
  printf("%c %u\n", (t),t);
  t = getc();
  printf("%c %u\n", (t),t);

  for (;;)
    asm("hlt");
}
