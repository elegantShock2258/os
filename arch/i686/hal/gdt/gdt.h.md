# gdt.h

## Description
Definitions for the Global Descriptor Table (GDT), segment descriptors, and related structures for memory segmentation.

## Imports
- [[kernel_utils.h.md]]

## Types
- `struct gdtr`: Size and base of the GDT.
- `struct gdt_entry`: Defines a single segment descriptor.

## Functions
- `void gdt_set_entry_info(...)`: Static declaration to set up a descriptor.
- `void gdt_init()`: Initializes the GDT with kernel and user segments.
