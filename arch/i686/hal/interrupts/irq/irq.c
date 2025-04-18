#pragma once
#include "irq.h"

#include "../../io/printf.c"
#include "../isr/isr.c"
#include "../pic/pic.c"
#include "../pit/pit.c"
#define PIC_REMAP_OFFSET 0x20

IRQHandler g_IRQHandlers[16];

void i686_IRQ_Handler(Registers *regs) {
  int irq = regs->interrupt - PIC_REMAP_OFFSET;

  if (g_IRQHandlers[irq] != NULL) {
    // handle IRQ
    g_IRQHandlers[irq](regs);
  } else {
    u8 pic_isr = PIC_ReadInServiceRegister();
    u8 pic_irr = PIC_ReadIrqRequestRegister();

    printf("Unhandled IRQ %d  ISR=%x  IRR=%x...\n", irq, pic_isr, pic_irr);
  }
  PIC_SendEndOfInterrupt(irq);
}
void IRQ_RegisterHandler(int irq, IRQHandler handler) {
  g_IRQHandlers[irq] = handler;
}

void irq_init() {
  PIC_Configure(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);

  // register ISR handlers for each of the 16 irq lines
  for (int i = 0; i < 16; i++) {
    PIC_Unmask(i);
    ISR_RegisterHandler(PIC_REMAP_OFFSET + i, i686_IRQ_Handler);
  }

  // enable interrupts
  asm("sti");
  IRQ_RegisterHandler(0, timer);
}
