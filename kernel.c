#include "io/printf.c"
#include "./descriptors/GDT/GDT.c"
#include "./descriptors/IDT/IDT.c"
#include "main.c"


#if defined(__linux__)
  #error use i686-elf-as command
#endif

void init(void){
  TermInit(); // for term init
  gdt_init(); // for gdt init
  idt_init(); // for idt init
  for(int i=0; i<VGA_WIDTH;i++) printf("-");
  printf("\n\n");
}

void kernel_main(void){
  init();
  main();
}

