# gdt.c

## Description
Implementation of Global Descriptor Table setup, defining memory segments for code, data, and userland.

## Imports
- [[gdt.h.md]]
- [[kernel_utils.c.md]]
- [[idt.c.md]]

## Variables
- `gdt_entry gdt_entries[7]`

## Functions
- `static void gdt_set_entry_info(...)`: Populates a `gdt_entry` struct.
- `void gdt_init()`: Sets up the null, kernel code/data, user code/data, and TSS segments, loads the GDT via `lgdt`, and reloads segments.
