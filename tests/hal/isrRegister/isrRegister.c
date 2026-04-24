#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/interrupts/isr/isr.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/memory.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

static bool customHandlerCalled = false;
void customTestHandler(Registers *regs) {
  (void)regs;
  customHandlerCalled = true;
}

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;

  // pick a high interrupt number unlikely to fire during test
  int testInterrupt = 100;

  // before registration, handler should be NULL
  res = res && (g_ISRHandlers[testInterrupt] == NULL);

  // register our handler
  ISR_RegisterHandler(testInterrupt, customTestHandler);

  // after registration, handler should be non-NULL
  res = res && (g_ISRHandlers[testInterrupt] != NULL);

  // verify it points to our function
  res = res && (g_ISRHandlers[testInterrupt] == customTestHandler);

  assert(res, "ISR handler registration working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
