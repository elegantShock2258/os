.globl loadPageDirectory
loadPageDirectory:
push %ebp
mov %esp, %ebp
mov 8(%esp), %eax
mov %eax, %cr3
mov %ebp, %esp
pop %ebp
ret

.globl enablePaging
enablePaging:
push %ebp
mov %esp, %ebp
mov %cr0, %eax
orl $80000000, %eax # should be divisile by 4096
mov %eax, %cr0
mov %ebp, %esp
pop %ebp
ret
 