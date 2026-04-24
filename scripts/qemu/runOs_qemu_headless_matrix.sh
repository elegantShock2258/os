#!/bin/bash

rm -rf build build/output
mkdir -p build build/output
cd build/output

set -e

PROJECT_ROOT="../.."

KERNEL_C="$PROJECT_ROOT/kernel.c"
MAIN_C="$PROJECT_ROOT/main.c"
OUTPUT_BIN="myos.bin"

MEMORY="128M"
SMP="1"
if [ "$#" -ge 5 ]; then
  SMP="$5"
fi
if [ "$#" -ge 1 ]; then
  KERNEL_C="$1"
fi
if [ "$#" -ge 2 ]; then
  MAIN_C="$2"
fi
if [ "$#" -ge 3 ]; then
  OUTPUT_BIN="$3"
fi
if [ "$#" -ge 4 ]; then
  MEMORY="$4"
fi

OUTPUT_DIR=$(dirname "$OUTPUT_BIN")
mkdir -p "./boot/$OUTPUT_DIR"

i686-elf-as $(find $PROJECT_ROOT -type f -name "*.S") -o boot.o
i686-elf-gcc -c "$KERNEL_C" -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra $EXTRA_CFLAGS
i686-elf-gcc -S "$KERNEL_C" -o kernel_asm.S -std=gnu99 -ffreestanding -O2 -Wall -Wextra $EXTRA_CFLAGS
i686-elf-gcc -T "$PROJECT_ROOT/linker.ld" -o temp.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

mv temp.bin "./boot/$OUTPUT_BIN"
i686-elf-size "./boot/$OUTPUT_BIN"

mkdir -p ./boot/grub
cp "$PROJECT_ROOT/grub.cfg" ./boot/grub/grub.cfg
grub-mkrescue -o myos.iso .

qemu-system-i386 \
  -cdrom myos.iso \
  -m $MEMORY \
  -smp $SMP \
  -vga std \
  -serial file:out \
  -device isa-debug-exit \
  -display none \
  -no-reboot