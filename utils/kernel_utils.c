#pragma once
#include "../io/printf.h"

int kernel_log(const char *fmt, ...) {
  int res = -1;
  va_list va;
  va_start(va, fmt);
  printf("KERNEL: ");
  res = printf_(fmt, va);
  va_end(va);
  return res;
}