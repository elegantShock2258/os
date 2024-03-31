.text
.extern ISR_Handler

.macro ISR_NOERRORCODE num
.global ISR\num
ISR\num:
  pushl $0       # Push dummy error code
  pushl $\num      # Push interrupt number
  jmp isr_common
.endm

.macro ISR_ERRORCODE num
.global ISR\num
ISR\num:
       #  CPU pushes an error code to the stack
  pushl $\num      # Push interrupt number
  jmp isr_common
.endm

.include "/home/a/projects/os/descriptors/IDT/isrs_gen.inc"

isr_common:
  pushal       # Pushes in order: eax, ecx, edx, ebx, esp, ebp, esi, edi

  xorl %eax, %eax  # Push ds
  movw %ds, %ax
  pushl %eax

  movw $0x10, %ax   # Use the kernel data segment
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  pushl %esp      # Pass the pointer to the stack to C
  call ISR_Handler
  addl $4, %esp

  popl %eax        # Restore the old segment
  movw %ax, %ds
  movw %ax, %es
  movw %ax, %fs
  movw %ax, %gs

  popal         # Pop what we pushed with pusha
  addl $8, %esp     # Remove error code and interrupt number
  iret          # Will pop: cs, eip, eflags, ss, esp
