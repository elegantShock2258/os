#include "../../../arch/i686/hal/hal.c"
#include "../../../arch/i686/hal/paging/paging.c"
#include "../../../drivers/drivers.c"
#include "../../../multiboot.h"
#include "getNthBit.c"

#if defined(__linux__)
#error use i686-elf-as command
#endif

multiboot_info_t *multiboot_grub_info;
void init(unsigned long ebx) {
  hal_init();
  drivers_init(ebx);
  paging_init();
}

void kernel_main(unsigned long ebx) {
  init(ebx);
  printf("TEST: GETNTHBIT\n");
  main();
}
