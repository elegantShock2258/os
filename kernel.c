#include "./multiboot.h"
#include "arch/i686/hal/hal.c"
#include "drivers/drivers.c"
#include "arch/i686/hal/paging/paging.c"
#include "arch/i686/hal/memory/kheap/kheap.c"
#include "main.c"

#if defined(__linux__)
#error use i686-elf-as command
#endif

multiboot_info_t *multiboot_grub_info;
void init(unsigned long ebx) {
  hal_init();
  drivers_init(ebx); // initialize drivers 
  paging_init(); // enable paging after getting multiboot info
  bitmap_init();
}

void kernel_main(unsigned long ebx) {
  init(ebx);
  main();
}
