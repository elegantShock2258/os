#include "io/printf.c"
#include "./descriptors/GDT/GDT.c"
#include "main.c"


#if defined(__linux__)
  #error use i686-elf-as command
#endif

void init(void){
  TermInit(); // for term init
  gdt_init(); // for gdt init
}

void kernel_main(void){
  init();
  main();
}

