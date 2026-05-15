# paging.c

## Description
Implementation of paging, setting up Physical Address Extension (PAE) and mapping virtual addresses to physical.

## Imports
- [[paging.h.md]]
- [[kernel_utils.c.md]]

## Variables
- `page_dir_ptr_tab[4]`, `page_dir[512]`

## Functions
- `void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys)`
- `void *get_physaddr(void *virtualaddr)`
- `void paging_init()`: Configures page directories, enables PAE and turns on paging.
- `void page_fault()`: Basic handler.
