#pragma once 
#include "../../utils/kernel_utils.h"
#include "../../io/printf.h"

typedef struct {
  u16 BaseLow;
  u16 SegmentSelector;
  u8 Reserved;
  u8 Flags;
  u16 BaseHigh;
} __attribute__((packed)) IDTEntry;

typedef struct {
  u16 limit;
  IDTEntry *base;
} __attribute__((packed)) idtr_t;



#define IDT_FLAG_GATE_TASK 0x5
#define IDT_FLAG_GATE_16BIT_INT 0x6
#define IDT_FLAG_GATE_16BIT_TRAP 0x7
#define IDT_FLAG_GATE_32BIT_INT 0xE
#define IDT_FLAG_GATE_32BIT_TRAP 0xF

#define IDT_FLAG_RING0 (0 << 5)
#define IDT_FLAG_RING1 (1 << 5)
#define IDT_FLAG_RING2 (2 << 5)
#define IDT_FLAG_RING3 (3 << 5)

#define IDT_FLAG_PRESENT 0x80


void IDT_EnableGate(int interrupt) ;

void IDT_DisableGate(int interrupt);

void idt_set_descriptor(u8 interrupt, void (*base)(), u8 flags);
void idt_init();

