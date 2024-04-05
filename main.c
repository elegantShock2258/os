#include "io/printf.c"
#include "pic/keyboard.c"
#include "pic/pic.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  printf("de"
         "hie %d\n",
         49);
  printf("a");
  asm("int $4");
  printf("b");
  asm("int $5");
  printf("c");

}
