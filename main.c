#include "./descriptors/IDT/irq.c"
#include "io/printf.c"
#include "pic/keyboard.c"
#include "pic/pic.c"

void timer(Registers *regs) { printf("."); }
void keyboard(Registers *regs) {
  unsigned char scancode = keyboard_read_scan_code();
  unsigned char code = keyboard_scan_code_to_ascii(scancode);
  printf("\n%c\n", code);
}
void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  printf("de"
         "hie %d\n",
         49);
  IRQ_RegisterHandler(0, timer);
  IRQ_RegisterHandler(1, keyboard);

  for (;;)
    asm("hlt");
}
