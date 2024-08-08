#pragma once
#include "../arch/i686/hal/io/printf.h"
#include "./kernel_utils.h"
#include <stddef.h>
#include <stdint.h>

int abs(int y){
  if(y>=0) return y;
  else return -y;
}

int kernel_log(const char *fmt, ...) {
  int res = -1;
  va_list va;
  va_start(va, fmt);
  printf("KERNEL: ");
  res = printf_(fmt, va);
  va_end(va);
  return res;
}