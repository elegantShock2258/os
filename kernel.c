#include "io/print.c"
#include "main.c"


#if defined(__linux__)
  #error use i686-elf-as command
#endif

void init(void){
  TermInit(); // for term init
}

void kernel_main(void){
  init();
  main();
}

