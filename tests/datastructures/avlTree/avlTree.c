#include "../../../utils/ds/AvlTree/AvlTree.c"
#include "../../../arch/i686/hal/interrupts/irq/irq.c"
#include "../../../arch/i686/hal/io/printf.c"
#include "../../../arch/i686/hal/io/printf.h"
#include "../../../arch/i686/hal/io/serial.c"
#include "../../../arch/i686/hal/io/stdio.c"
#include "../../../arch/i686/hal/memory/kheap/kheap.c"
#include "../../../drivers/vbe/vbe.c"
#include "../../../utils/kernel_utils.c"
#include "../../testing.c"

// comparator required by the AVL tree
int _AVL_comparitor(void *a, void *b) { return (*(int *)a) - (*(int *)b); }

void main(void) {
  terminal_color = vga_entry_color(WHITE, BLACK);
  bool res = true;

  // initialize bitmap allocator so kmalloc works for tree nodes
  bitmap_init();

  int val1 = 10, val2 = 20, val3 = 30;
  u32 h1, h2, h3;
  Node *root = NULL;

  // insert 3 nodes (enough to test balancing without too many allocs)
  root = insert(root, &val1, &h1);
  res = res && (root != NULL);

  root = insert(root, &val2, &h2);
  res = res && (root != NULL);

  root = insert(root, &val3, &h3);
  res = res && (root != NULL);

  // tree should be balanced: |balance factor| <= 1
  int bf = getBalanceFactor(root);
  res = res && (bf >= -1 && bf <= 1);

  // height should be > 0
  int h = getHeight(root);
  res = res && (h > 0);

  assert(res, "AVL tree insert and balance working properly");
  killQemu();
  for (;;)
    asm("hlt");
}
