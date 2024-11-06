// each thread is a flow of execution.
// ---- Thread Control Block STRUCT ----
// 1) Thread ID.
// 2) Stack Pointer: for threads stack
// 3) Program Counter: points to latest instruction
// 4) state of thread : running, ready,waiting,start,done
// 5) Registers: thread resgister values
// 6) PCB: pointer to the PCB of the thread