.global gdt_flush      /* Allows the C code to call gdt_flush(). */

gdt_flush:
    mov 4(%esp), %eax  /* Get the pointer to the GDT, passed as a parameter. */
    lgdt 4(%esp)        /* Load the new GDT pointer */

    mov %ax, 0x10      /* 0x10 is the offset in the GDT to our data segment */
    mov %ds, %ax        /* Load all data segment selectors */
    mov %es, %ax
    mov %fs, %ax
    mov %gs, %ax
    mov %ss, %ax
    jmp .flush   /* 0x08 is the offset to our code segment: Far jump! */
.flush:
    ret
