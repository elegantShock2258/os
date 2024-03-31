#include "io/printf.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  printf("de" "hie %d\n", 49);
  asm("int $4");
}
