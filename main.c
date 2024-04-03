#include "io/printf.c"
#include "pic/keyboard.c"
#include "pic/pic.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  printf("de"
         "hie %d\n",
         49);
  
  unsigned char scancode = keyboard_read_scan_code();
  char asciicode[2];
  asciicode[0] = keyboard_scan_code_to_ascii(scancode);

  printf("%s %d", asciicode,scancode);
  serial_write(asciicode,sizeof(asciicode));
}
