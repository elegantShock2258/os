#include "io/printf.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  printf("hie %d", 49);
  asm("int $0x01");
}
