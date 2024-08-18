
#include "./keyboard/keyboard.c"
#include "./mouse/mouse.c"
#include "./vbe/vbe.c"

void drivers_init(int ebx) {


  KeyboardConstructor();
  MouseConstructor();
  VbeConstructor(ebx);

}