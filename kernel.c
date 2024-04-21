#include "./multiboot.h"
#include "arch/i686/hal/hal.c"
#include "arch/i686/hal/vbe/vbe.c"
#include "arch/i686/hal/vbe/vbe.h" // TODO: add svda_mode_info_t to c file
#include "main.c"
#include <stdint.h>

#if defined(__linux__)
#error use i686-elf-as command
#endif

multiboot_info_t *multiboot_grub_info;
void init(void) {
  hal_init();
  // apparently ur using multiboot 2
}

void kernel_main(unsigned long ebx) {
  init();
  multiboot_grub_info = (multiboot_info_t *) ebx;
  vbe_info(multiboot_grub_info);
  printf("magic: %s %u\n", vbe_control_block->VbeSignature,vbe_control_block->VbeVersion);
  main();
}
