#include "arch/i686/io/printf.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  printf("de"
         "hie %d\n",
         49);
  for (int i = 0; i < 100; i++)
    printf("fg %d\n", i);
  printf("%d %d %d", 'K', vga_entry_color(LIGHT_GREY, BLACK), getcolor(0, 0));

  for (;;)
    asm("hlt");
}
