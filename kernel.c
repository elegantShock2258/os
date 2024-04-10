#include "arch/i686/hal/hal.c"
#include "main.c"

#if defined(__linux__)
  #error use i686-elf-as command
#endif

void init(void){
  hal_init();
}

void kernel_main(void){
  init();
  main();
}

