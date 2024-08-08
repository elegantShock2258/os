#include "./multiboot.h"
#include "arch/i686/hal/hal.c"
#include "drivers/vbe/vbe.c"
#include "arch/i686/hal/paging/paging.c"
#include "main.c"

#if defined(__linux__)
#error use i686-elf-as command
#endif

multiboot_info_t *multiboot_grub_info;
void init(unsigned long ebx) {
  hal_init();
  multiboot_grub_info = (multiboot_info_t *) ebx;
  
  paging_init(); // enable paging after getting multiboot info

  vbe_mode_info_structure * t = vbe_info(multiboot_grub_info);
}

void kernel_main(unsigned long ebx) {
  init(ebx);
  main();
}
