// process is a collection of system resources
// it has a pcb, containing an address space
// a linked list of threads
// store all pcbs in a process table, make it like a vector
// store the current directory of a process in pcb
// store permissions for a process


// ---- PCB STRUCT ---- 
// 1) a process SCHEDULING state: new, ready, running,waiting,terminated
// 2) a process structure info: child process ids(maybe a liked list of the child process pcbs) or ids of other processes related
// 3) IPC flags: stuff like signals, messages, etc for IPC
// 4) privelages: what resouces are allowed
// 5) a process state: new, ready, running, waiting, dead
// 6) PID
// 7) Program Counter: a pointer to the next instruction of the process
// 8) CPU Registers: a Registers Struct to store all register data
// 9) CPU Scheduling Information: a ptr for scheduling information
// 10) Memory Management Information: a ptr for page table, memory limits, and segment table
// 11) Accounting Information: CPU %, RAM %, time and execution ids
// 12) IO Status information: list of I/O devices that are allocated to the proccess


// PCB is placed at the bottom of the process stack