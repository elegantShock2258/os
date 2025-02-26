#pragma once
#include "../../../kernel/syscalls/syscalls.h"
#include "../../kernel_utils.c"
typedef struct Node {
  void *key;
  struct Node *left;
  struct Node *right;
  u32 *height;
} Node;