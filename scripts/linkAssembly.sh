rm -rf build build/output
mkdir -p build build/output
cd build/output

PROJECT_ROOT="../.."
# compile the boot code, kernel.c and link them from the linker
i686-elf-as $(find $PROJECT_ROOT -type f -name "*.S") -o boot.o
i686-elf-gcc -c "$PROJECT_ROOT/kernel.c" -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -S "$PROJECT_ROOT/kernel.c" -o kernel_asm.S -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T "$PROJECT_ROOT/linker.ld" -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

