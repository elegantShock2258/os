#pragma once
#include "../../kernel_utils.c"
#define _CB_TYPE int // NOTE: this is a shitty implementation of
// generics, jus either change this macro or use void pointers for your
// datatype.
typedef struct {
  void **data;
  size_t head;
  size_t tail;
  bool full;
  int size;
} _CircularBuffer;

typedef struct  CircularBuffer {
  bool (*isEmpty)(const struct CircularBuffer *cb);
  bool (*isFull)(const struct CircularBuffer *cb);
  void (*enqueue)(struct CircularBuffer *cb, uint8_t value);
  bool (*dequeue)(struct CircularBuffer *cb, uint8_t *value);
  void (*Constructor)();

  _CB_TYPE (*top)(const struct CircularBuffer *cb);

  _CircularBuffer *_cb; // for internal use only
} CircularBuffer;
