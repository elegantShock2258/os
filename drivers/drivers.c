#include "../multiboot.h"

#include "./keyboard/keyboard.c"
#include "./mouse/mouse.c"
#include "./vbe/vbe.c"

void drivers_init(int ebx) {

  multiboot_info_t * multiboot_grub_info = (multiboot_info_t *)ebx;

  KeyboardConstructor();
  MouseConstructor();

  vbe_init(multiboot_grub_info);

}