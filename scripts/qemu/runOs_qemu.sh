#!/bin/bash

rm -rf build build/output
mkdir -p build build/output
cd build/output

set -e

PROJECT_ROOT="../.."

# Default file paths
KERNEL_C="$PROJECT_ROOT/kernel.c"
MAIN_C="$PROJECT_ROOT/main.c"
OUTPUT_BIN="myos.bin"

# Check and replace paths if arguments are given
if [ "$#" -ge 1 ]; then
  KERNEL_C="$1"
fi
if [ "$#" -ge 2 ]; then
  MAIN_C="$2"
fi
if [ "$#" -ge 3 ]; then
  OUTPUT_BIN="$3"
fi

# Ensure the output directory structure exists
OUTPUT_DIR=$(dirname "$OUTPUT_BIN")
# Create the full path for the output directory
mkdir -p "./boot/$OUTPUT_DIR"

# Compile the boot code, kernel.c, and link them using the linker
i686-elf-as $(find $PROJECT_ROOT -type f -name "*.S") -o boot.o
i686-elf-gcc -c "$KERNEL_C" -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -S "$KERNEL_C" -o kernel_asm.S -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T "$PROJECT_ROOT/linker.ld" -o temp.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

# Copy the binary to the appropriate location in /boot
mv temp.bin "./boot/$OUTPUT_BIN"

# Create GRUB image
mkdir -p ./boot/grub
cp "$PROJECT_ROOT/grub.cfg" ./boot/grub/grub.cfg
grub-mkrescue -o myos.iso .

# Run the image in QEMU
qemu-system-i386 -cdrom myos.iso -vga std
