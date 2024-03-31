#pragma once
#include "../../utils/kernel_utils.h"

struct gdtr {
  u16 limit;               // -> size of GDT
  u32 base;                // -> ptr to GDT
} __attribute__((packed)); // do the attribute shit so gcc doesnt include some
                           // optimisation bits
typedef struct gdtr gdtr;

//---------------------------------------------------------------------------------------------
// Look at the GDT Entry picture to understand the stuct
// Limit 0:7 Limit 8:15 Base 0:7 base 7:15 base 16:23 Access Byte Flags Limit
// 16:19 Base 24:91
//---------------------------------------------------------------------------------------------
struct gdt_entry {
  // theres only one base thing i think, for some reason its distributed like in
  // the pic
  u16 limit_low;
  u16 base_low;
  u8 base_middle;
  u8 access;
  u8 granularity; // this includes the flags and limits in the pic
  u8 base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry;

struct gdt_ptr {
  u16 limit;       // start address
  gdt_entry *base; // size
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr;



/**
 * @brief Sets the information for a GDT entry.
 *
 * @param num The index of the GDT entry to set.
 * @param base The base address of the segment.
 * @param limit The size of the segment, in bytes.
 * @param access The access flags for the segment.
 * @param gran The granularity of the segment.
 */
static void gdt_set_entry_info(u32 num, u32 base, u32 limit, u8 access,
                               u8 gran) ;

// ill add these entries to the GDT
// some null entry first too
// "code": kernel code, used to stored the executable binary code
// "data": kernel data
// "stack": kernel stack, used to stored the call stack during kernel execution
// "ucode": user code, used to stored the executable binary code for user
// program
// "udata": user program data
// "ustack": user stack, used to stored the call stack during execution in
// userland

void gdt_init();