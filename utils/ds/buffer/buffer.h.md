# buffer.h

## Description
Header for a Circular Buffer structure used largely by device drivers (like keyboard) to store pending events/characters.

## Imports
- [[kernel_utils.c.md]]

## Types
- `_CircularBuffer`: Internal structure.
- `CircularBuffer`: Object-oriented style interface containing function pointers to methods like `enqueue`, `dequeue`, `isFull`.
