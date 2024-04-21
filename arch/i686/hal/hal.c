#pragma once

#include "hal.h"

#include "gdt/gdt.c"
#include "interrupts/idt/idt.c"
#include "interrupts/irq/irq.c"
#include "interrupts/isr/isr.c"
#include "io/printf.c"
#include "io/serial.c"


void hal_init() {
  TermInit();             // for term init
  gdt_init(); // for gdt init
  idt_init();             // for idt init
  isr_init();             // for isr init
  irq_init();

  // paging_init(); // for paging init

  for (size_t i = 0; i < VGA_WIDTH; i++)
    printf("-");
  printf("\n\n");
}