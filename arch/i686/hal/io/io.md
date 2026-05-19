# io.md

## Directory: arch/i686/hal/io

Basic input/output interfaces for the OS, facilitating communication outside the main screen framebuffer.

### Components
- **Serial Debugging (`serial.c`)**: Initializes the COM1 serial port to allow the kernel to log output securely to the host machine or QEMU terminal without modifying the framebuffer. Implements `outb` and `inb`.
- **printf implementation (`printf.h`, `printf.c`)**: A minimal and embedded-friendly C `printf` implementation capable of parsing strings and variadic arguments. 
- **stdio (`stdio.c`)**: Handles higher-level string manipulation like `to_string()` for basic base conversions (int to string).
