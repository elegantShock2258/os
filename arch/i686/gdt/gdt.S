.globl reloadSegments
reloadSegments:
    # enable protection mode
    mov %cr0, %eax
    orb $1, %al       # set PE (Protection Enable) bit in CR0 (Control Register 0)
    mov %eax, %cr0

    # Reload CS register containing code selector:
    ljmp $0x08, $.reload_CS # 0x08 is a stand-in for your code segment

.reload_CS:
    # Reload data segment registers:
    movw $0x10, %ax # 0x10 is a stand-in for your data segment
    movw %ax, %ds
    movw %ax, %es
    movw %ax, %fs
    movw %ax, %gs
    movw %ax, %ss
    ret
