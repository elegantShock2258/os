#pragma once
#include "./kernel_utils.h"
#include "../arch/i686/hal/io/printf.h"
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int abs(int y) {
  if (y >= 0)
    return y;
  else
    return -y;
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

bool getNthBit(u32 data, int n) { return (data & (1 << n)); }

void setNthBit(u32 *data, int n, bool value) {
  if (value) {
    *data |= (1 << n);
  } else {
    *data &= ~(1 << n);
  }
}


int popcount(u32 n) {
  int count = 0;
  while (n) {
    count += n & 1;
    n >>= 1;
  }
  return count;
}

int findFirstUnSetBit(unsigned int n) {
  int position = 31;
  if (n == 0xffffffff)
    return -1;
  while (--position > 0 && (n & (1 << position)))
    ;
  return position;
}

void printBinary(u32 n){
  for(int i=31; i>=0; i--){
    printf("%d", getNthBit(n, i));
  }
  printf("\n");
}