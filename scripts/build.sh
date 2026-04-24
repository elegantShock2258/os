rm -rf build build/output
mkdir -p build build/output
cd build/output

set -e

PROJECT_ROOT="../.."

# Default toolchain
: ${CC:=i686-elf-gcc}
: ${AS:=i686-elf-as}

CFLAGS="-std=gnu99 -ffreestanding -O2 -Wall -Wextra $EXTRA_CFLAGS"
LDFLAGS="-T $PROJECT_ROOT/linker.ld -ffreestanding -O2 -nostdlib -lgcc $EXTRA_CFLAGS"

echo "Using compiler: $CC"

# If using clang, adjust behavior
if [[ "$CC" == *clang* ]]; then
    TARGET="--target=i686-elf"
    CFLAGS="$CFLAGS $TARGET"
    LDFLAGS="$LDFLAGS $TARGET"

    # Clang can compile .S directly
    $CC -c $(find $PROJECT_ROOT -type f -name "*.S") -o boot.o $CFLAGS
else
    # GCC toolchain
    $AS $(find $PROJECT_ROOT -type f -name "*.S") -o boot.o
fi

# Compile kernel
$CC -c "$PROJECT_ROOT/kernel.c" -o kernel.o $CFLAGS

# Generate assembly (optional debug)
$CC -S "$PROJECT_ROOT/kernel.c" -o kernel_asm.S $CFLAGS

# Link
$CC $LDFLAGS -o myos.bin boot.o kernel.o

# Create GRUB image
mkdir -p ./boot/grub
cp myos.bin ./boot/myos.bin
cp "$PROJECT_ROOT/grub.cfg" ./boot/grub/grub.cfg
grub-mkrescue -o myos.iso .