# kernel.md

## Directory: kernel

The `kernel` directory handles the primary initialization sequence of the operating system after the bootloader hands off execution.

### Key Files & Sub-modules
- `kernel.c`: The C entry point (`kernel_main`) invoked by `boot.S`. It sets up the Hardware Abstraction Layer (`hal_init`), drivers (`drivers_init`), and memory paging (`paging_init`) before yielding to `main()`.
- `main.c`: The core execution loop of the OS. Currently heavily relies on the VBE driver for running the graphical loop `VbeDriver.renderLoop()`.
- `boot.S`: The assembly stub that complies with Multiboot specifications and correctly aligns the CPU stack before diving into the kernel's C code.
- `multiboot.h`: Header detailing the standard multiboot structs (memory map, VESA info) passed by GRUB.

### Documentation References
These files are tightly integrated with the abstraction layers. Look into `arch/i686/hal/hal.md` for the underlying initialization steps called during the boot phase.


## Todo
Ring 3
Demand Paging
