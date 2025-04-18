// _exit ¶
// Exit a program without cleaning up files. If your system doesn’t provide this, it is best to avoid linking with subroutines that require it (exit, system).
// close ¶
// Close a file. Minimal implementation:
// environ ¶
// A pointer to a list of environment variables and their values. For a minimal environment, this empty list is adequate:
// execve ¶
// Transfer control to a new process. Minimal implementation (for a system without processes):
// fork ¶
// Create a new process. Minimal implementation (for a system without processes):
// fstat ¶
// Status of an open file. For consistency with other minimal implementations in these examples, all files are regarded as character special devices. The sys/stat.h header file required is distributed in the include subdirectory for this C library.
// getpid ¶
// Process-ID; this is sometimes used to generate strings unlikely to conflict with other processes. Minimal implementation, for a system without processes:
// isatty ¶
// Query whether output stream is a terminal. For consistency with the other minimal implementations, which only support output to stdout, this minimal implementation is suggested:
// kill ¶
// Send a signal. Minimal implementation:
// link ¶
// Establish a new name for an existing file. Minimal implementation:
// lseek ¶
// Set position in a file. Minimal implementation:
// open ¶
// Open a file. Minimal implementation:
// read ¶
// Read from a file. Minimal implementation:
// sbrk ¶
// Increase program data space. As malloc and related functions depend on this, it is useful to have a working implementation. The following suffices for a standalone system; it exploits the symbol _end automatically defined by the GNU linker.
// stat ¶
// Status of a file (by name). Minimal implementation:
// times ¶
// Timing information for current process. Minimal implementation:
// unlink ¶
// Remove a file’s directory entry. Minimal implementation:

// wait ¶
// Wait for a child process. Minimal implementation:

// write ¶
// Write to a file. libc subroutines will use this system routine for output to all files, including stdout—so if you need to generate any output, for example to a serial port for debugging, you should make your minimal write capable of doing this. The following minimal implementation is an incomplete example; it relies on a outbyte subroutine (not shown; typically, you must write this in assembler from examples provided by your hardware manufacturer) to actually perform the output.


#include "./malloc/malloc.c"