# buffer.c

## Description
Implementation of the Circular Buffer, allocating memory using `kmalloc`.

## Imports
- [[buffer.h.md]]
- [[kheap.c.md]]

## Functions
- `void _cb_init(CircularBuffer *cb, int size)`
- `bool _cb_is_empty(const CircularBuffer *cb)`
- `bool _cb_is_full(const CircularBuffer *cb)`
- `void _cb_enqueue(CircularBuffer *cb, _CB_TYPE *value)`
- `_CB_TYPE _cb_dequeue(CircularBuffer *cb, _CB_TYPE *value)`
- `_CB_TYPE _cb_top(CircularBuffer *cb)`
- `void _CB_Constructor(CircularBuffer *state, int size)`
