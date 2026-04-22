#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/kheap/kheap.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/ds/buffer/buffer.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;

  // initialize bitmap allocator — _CB_Constructor uses kmalloc internally
  bitmap_init();

  CircularBuffer cb;
  _CB_Constructor(&cb, 5);

  // should be empty initially
  res = res && cb.isEmpty(&cb);

  // enqueue multiple values
  int a = 10, b = 20, c = 30;
  cb.enqueue(&cb, &a);
  cb.enqueue(&cb, &b);
  cb.enqueue(&cb, &c);

  // top should return most recently enqueued
  _CB_TYPE topVal = cb.top(&cb);
  res = res && (topVal == 30);

  // dequeue should return first enqueued (FIFO)
  _CB_TYPE dq;
  _CB_TYPE val = cb.dequeue(&cb, &dq);
  res = res && (val == 10);

  // after dequeue, top should still be 30
  topVal = cb.top(&cb);
  res = res && (topVal == 30);

  assert(res, "circular buffer working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
