#pragma once
#include "paging.h"
#include "../../../../utils/kernel_utils.c"
// TODO: dynamic page allocation and deletion

static uint32_t *last_page = 0;

u64 page_dir_ptr_tab[4]
    __attribute__((aligned(0x20))); // must be aligned to (at least)0x20, ...
u64 page_dir[512]
    __attribute__((aligned(0x1000))); // must be aligned to page boundary

void paging_map_virtual_to_phys(uint32_t virt, uint32_t phys) {
  uint16_t id = virt >> 22;
  for (int i = 0; i < NUM_PAGES; i++) {
    last_page[i] = phys | 3;
    phys += PAGE_FRAME_SIZE;
  }
  page_dir[id] = ((uint32_t)last_page) | 3;
  last_page = (uint32_t *)(((uint32_t)last_page) + PAGE_FRAME_SIZE);
  printf("Mapping 0x%x (%d) to 0x%x\n", virt, id, phys);
}
void *get_physaddr(void *virtualaddr) {
  unsigned long pdindex = (unsigned long)virtualaddr >> 22;
  unsigned long ptindex = (unsigned long)virtualaddr >> 12 & 0x03FF;

  unsigned long *pd = (unsigned long *)0xFFFFF000;

  unsigned long *pt = ((unsigned long *)0xFFC00000) + (0x400 * pdindex);

  return (void *)((pt[ptindex] & ~0xFFF) +
                  ((unsigned long)virtualaddr & 0xFFF));
}

void paging_init() {
  // set the page directory into the PDPT and mark it present
  page_dir_ptr_tab[0] = (u64)&page_dir | 1;
  page_dir[0] = 0b10000011; // Address=0, 2MIB, RW and present

  paging_map_virtual_to_phys(0, 0);
  paging_map_virtual_to_phys(0x400000, 0x400000);

  // set bit5 in CR4 to enable PAE
  asm volatile("movl %%cr4, %%eax; bts $5, %%eax; movl %%eax, %%cr4" ::: "eax");
  // load PDPT into CR3
  asm volatile("movl %0, %%cr3" ::"r"(&page_dir_ptr_tab));

  asm volatile("movl %%cr0, %%eax; orl $80000000, %%eax; movl %%eax, %%cr0;" ::
                   : "eax");
}

void page_fault() {
  char msg[] = "Page Error";
  printf("dwag u fucked up paging");
}