# paging.h

## Description
Header for memory paging structures and flags for x86 architecture.

## Types
- `page_t`: Structure of a single 32-bit page table entry.
- `page_table_t`: A table of 1024 pages.
- `page_directory_t`: A directory holding pointers to page tables.

## Functions
- `void init_paging()`
- `void page_fault()`
