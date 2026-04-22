#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/memory.c"
#include "../../../drivers/keyboard/keyboard.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;

  // KeyboardConstructor() was called in drivers_init()
  // verify function pointers are set
  res = res && (KeyboardDriver.keyboard_read_scan_code != NULL);
  res = res && (KeyboardDriver.keyboard_scan_code_to_ascii != NULL);
  res = res && (KeyboardDriver.keyboard != NULL);
  res = res && (KeyboardDriver.Constructor != NULL);

  // verify scancode -> ascii lookup: 0x1E should map to 'a'
  // the lookup table is the static 'ascii[]' array in keyboard.c
  unsigned char a_key = KeyboardDriver.keyboard_scan_code_to_ascii(0x1E);
  res = res && (a_key == 'a');

  // 0x10 should map to 'q'
  unsigned char q_key = KeyboardDriver.keyboard_scan_code_to_ascii(0x10);
  res = res && (q_key == 'q');

  // 0x02 should map to '1'
  unsigned char one_key = KeyboardDriver.keyboard_scan_code_to_ascii(0x02);
  res = res && (one_key == '1');

  // verify release map is initialized to zeros
  res = res && (KeyboardDriver.releaseMap[0] == 0);

  assert(res, "keyboard init and scancode table working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
