rm -rf output
mkdir -p output
cd output
# compile the boot code, kernel.c and link them from the linker
i686-elf-as $(find .. -type f -name "*.S") -o boot.o
i686-elf-gcc -c ../kernel.c -o kernel.o -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -S ../kernel.c -o kernel_asm.S -std=gnu99 -ffreestanding -O2 -Wall -Wextra
i686-elf-gcc -T ../linker.ld -o myos.bin -ffreestanding -O2 -nostdlib boot.o kernel.o -lgcc

#  make grub image 
mkdir -p ./boot/grub
cp myos.bin ./boot/myos.bin
cp ../grub.cfg ./boot/grub/grub.cfg
grub-mkrescue -o myos.iso .
# run the image in qemu
qemu-system-i386 -cdrom myos.iso -vga std 

