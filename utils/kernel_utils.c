#pragma once
#include "./kernel_utils.h"
#include "../arch/i686/hal/io/printf.c"
#include "../tests/testing.c"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

int abs(int y) {
  if (y >= 0)
    return y;
  else
    return -y;
}
int max(int a, int b) { return a > b ? a : b; }
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

void printBinary(u32 n) {
  terminal_color = LIGHT_GREY;
  terminal_color = WHITE;
  bool one = 0;
  for (int i = 30; i >= 0; i--) {
    int bit = getNthBit(n, i);
    if (bit && !one) {
      terminal_color = LIGHT_GREY;
      printf("%d", bit);
      terminal_color = WHITE;
      one = true;
    } else if (!bit) {
      one = false;
    }
    printf("%d", getNthBit(n, i));
  }
  printf("\n");
}
void logBinary(u32 n) {
  bool one = 0;
  for (int i = 30; i >= 0; i--) {
    int bit = getNthBit(n, i);
    if (bit && !one) {
      outputQemuMessage(bit ? "1" : "0");
      one = true;
    } else if (!bit) {
      one = false;
    }
    outputQemuMessage(getNthBit(n, i) ? "1" : "0");
  }
  outputQemuMessage("\n");
}