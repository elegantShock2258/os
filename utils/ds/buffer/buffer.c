#pragma once
#include "./buffer.h"
#include "../../../arch/i686/hal/memory/kheap/kheap.c"

void _cb_init(CircularBuffer *cb, int size) {
  cb->_cb->head = 0;
  cb->_cb->tail = 0;
  cb->_cb->full = false;
  cb->_cb->size = size;

  cb->_cb->data = kmalloc(size * sizeof(void *));
}

bool _cb_is_empty(const CircularBuffer *cb) {
  return (!cb->_cb->full && (cb->_cb->head == cb->_cb->tail));
}

bool _cb_is_full(const CircularBuffer *cb) { return cb->_cb->full; }

void _cb_enqueue(CircularBuffer *cb, _CB_TYPE value) {
  cb->_cb->data[cb->_cb->head] = (void*) &value;
  if (cb->_cb->full) {
    cb->_cb->tail = (cb->_cb->tail + 1) % cb->_cb->size;
  }
  cb->_cb->head = (cb->_cb->head + 1) % cb->_cb->size;
  cb->_cb->full = (cb->_cb->head == cb->_cb->tail);
}

bool _cb_dequeue(CircularBuffer *cb, _CB_TYPE *value) {
  if (_cb_is_empty(cb))
    return false;

  *value = *(_CB_TYPE *)(cb->_cb->data[cb->_cb->tail]);
  cb->_cb->full = false;
  cb->_cb->tail = (cb->_cb->tail + 1) % cb->_cb->size;
  return true;
}

_CB_TYPE _cb_top(CircularBuffer *cb) {
  return *(_CB_TYPE *)(cb->_cb->data[cb->_cb->tail]);
}
void _CB_Constructor(CircularBuffer *state, int size) {

  state->_cb = (_CircularBuffer *)kmalloc(sizeof(_CircularBuffer));

  state->isEmpty = _cb_is_empty;
  state->isFull = _cb_is_full;
  state->enqueue = _cb_enqueue;
  state->dequeue = _cb_dequeue;
  state->top = _cb_top;

  state->Constructor = _CB_Constructor;

  _cb_init(state, size);
}
