#include "../../../arch/i686/hal/gdt/gdt.c"
#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/memory.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;

  // gdt_init() ran in hal_init(). Verify the CPU loaded the correct
  // segment selectors by reading CS and DS registers.

  u32 cs_val, ds_val, ss_val;
  asm volatile("movl %%cs, %0" : "=r"(cs_val));
  asm volatile("movl %%ds, %0" : "=r"(ds_val));
  asm volatile("movl %%ss, %0" : "=r"(ss_val));

  // CS should be 0x08 (kernel code segment = GDT entry 1)
  res = res && ((cs_val & 0xFFFF) == 0x08);

  // DS should be 0x10 (kernel data segment = GDT entry 2)
  res = res && ((ds_val & 0xFFFF) == 0x10);

  // SS should also be 0x10
  res = res && ((ss_val & 0xFFFF) == 0x10);

  assert(res, "GDT init and segment selectors working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
