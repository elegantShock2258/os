#ifndef ___IDTC
#define ___IDTC

#include "../../utils/kernel_utils.c"
#include "../../utils/types.h"

// general isr
__attribute__((noreturn))
void exception_handler(void);
void exception_handler() {
    __asm__ volatile ("cli; hlt"); // Completely hangs the computer
}

typedef struct {
	u16    isr_low;      // The lower 16 bits of the ISR's address
	u16    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	u8     reserved;     // Set to zero
	u8     attributes;   // Type and attributes; see the IDT page
	u16    isr_high;     // The higher 16 bits of the ISR's address
} __attribute__((packed)) idt_entry_t;

__attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; 

typedef struct {
	u16	limit;
	u32	base;
} __attribute__((packed)) idtr_t;


static idtr_t idtr;

void idt_set_descriptor(u8 vector, void* isr, u8 flags);
void idt_set_descriptor(u8 vector, void* isr, u8 flags) {
    idt_entry_t* descriptor = &idt[vector];
 
    descriptor->isr_low        = (u32)isr & 0xFFFF;
    descriptor->kernel_cs      = 0x08; // this value can be whatever offset your kernel code selector is in your GDT
    descriptor->attributes     = flags;
    descriptor->isr_high       = (u32)isr >> 16;
    descriptor->reserved       = 0;
}

extern void* isr_stub_table[];
 
void idt_init(void);
void idt_init() {
    idtr.base = (u64)&idt[0];
    idtr.limit = (u16)sizeof(idt_entry_t) * (256 - 1);
 
    for (u8 vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        // kernel_log("IDT: set idt descriptor %d for %d\n",vector,isr_stub_table[vector]);
        // vectors[vector] = true;
    }
 
    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // enable interrupts
    kernel_log("IDT: done\n");
}

#endif