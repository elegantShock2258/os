#pragma once

#include "hal.h"

#include "gdt/gdt.c"
#include "interrupts/idt/idt.c"
#include "interrupts/irq/irq.c"
#include "interrupts/isr/isr.c"
#include "io/printf.c"
#include "io/serial.c"
#include "paging/paging.c"

void hal_init() {
  TermInit(); // for term init
  gdt_init(); // for gdt init   --------------------------- DISABLE INTERRUPTS 
  idt_init(); // for idt init
  isr_init(); // for isr init
  irq_init(); // ------------------------------------------ ENABLE INTERRUPTS

  for (size_t i = 0; i < VGA_WIDTH; i++)
    printf("-");
  printf("\n\n");
}