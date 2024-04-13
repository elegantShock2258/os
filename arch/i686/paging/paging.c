#pragma once
#include "../utils/kernel_utils.c"

u32 page_directory[1024] __attribute__((aligned(4096)));
u32 page_dir_ptr_tab[4] __attribute__((aligned(0x20))); // must be aligned to (at least)0x20, ...

extern void loadPageDirectory(unsigned int*);
extern void enablePaging();

void paging_init() {
  // initialising page directories
  for (int i = 0; i < 1024; i++) { // FIXME: init all 1024 pages?
    u32 page_table[1024] __attribute__((aligned(4096)));
    // holds the physical address where we want to start mapping these pages
    // to in this case, we want to map these pages to the very beginning of
    // memory.
    // we will fill all 1024 entries in the table, mapping 4 megabytes
    for (unsigned int k = 0; k < 1024; k++) {
      // As the address is page aligned, it will always leave 12 bits zeroed.
      // Those bits are used by the attributes
      // attributes: supervisor level, read/write, present.
      page_table[k] = (k * 0x1000) | 3;
    }
    page_directory[i] = ((u32)page_table[i]) | 3;
  }
  loadPageDirectory(page_directory);
  enablePaging();
}