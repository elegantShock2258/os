# utils.md

## Directory: utils

Provides utility functions, mathematical helpers, and critical data structures used across the operating system.

### Core Utilities
- `kernel_utils.c` / `kernel_utils.h`: Includes basic macros, mathematical logic (`max`, `abs`), bitwise utilities (`getNthBit`, `popcount`), and the central `kernel_log` wrapper.
- `types.h`: Type definitions representing absolute bit widths (`u8`, `u16`, `u32`, `u64`).
- `binary.h`: Flag mutation macros (`FLAG_SET`, `FLAG_UNSET`).

### Data Structures (`utils/ds`)
- **Circular Buffer (`buffer.c`)**: A standard ring buffer utilized prominently by the `keyboard` driver to handle scancode backlogs. Uses object-style struct methods (`cb->enqueue`, `cb->dequeue`).
- **AVL Tree (`AvlTree.c`)**: A self-balancing binary search tree. Used extensively by the VBE graphics Window Manager to organize and render windows in Z-index order.
