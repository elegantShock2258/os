#pragma once

#include "hal.h"
#include "../io/printf.c"
#include "../descriptors/GDT/GDT.c"
#include "../descriptors/IDT/IDT.c"
#include "../descriptors/IDT/isr.c"
#include "../pic/pic.c"

void hal_init(){
  TermInit(); // for term init
  gdt_init(); // for gdt init
  idt_init(); // for idt init
  isr_init(); // for isr init
  pic_init(); // for pic init
  for(size_t i=0; i<VGA_WIDTH;i++) printf("-");
  printf("\n\n");
}