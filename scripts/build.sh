rm -rf build build/output
mkdir -p build build/output
cd build/output

set -e

PROJECT_ROOT="../.."

: ${CC:=i686-elf-gcc}
: ${AS:=i686-elf-as}

CFLAGS="-std=gnu99 -ffreestanding -O2 -Wall -Wextra $EXTRA_CFLAGS"
LDFLAGS="-T $PROJECT_ROOT/linker.ld -ffreestanding -O2 -nostdlib -lgcc $EXTRA_CFLAGS"

echo "Using compiler: $CC"

OBJ_FILES=""

# 🔹 Compile all .S files individually
for file in $(find $PROJECT_ROOT -type f -name "*.S"); do
    obj="$(basename "$file" .S).o"

    if [[ "$CC" == *clang* ]]; then
        $CC --target=i686-elf -c "$file" -o "$obj" $CFLAGS
    else
        $AS "$file" -o "$obj"
    fi

    OBJ_FILES="$OBJ_FILES $obj"
done

# 🔹 Compile kernel
if [[ "$CC" == *clang* ]]; then
    TARGET="--target=i686-elf"
else
    TARGET=""
fi

$CC $TARGET -c "$PROJECT_ROOT/kernel.c" -o kernel.o $CFLAGS
OBJ_FILES="$OBJ_FILES kernel.o"

# 🔹 Optional ASM output
$CC $TARGET -S "$PROJECT_ROOT/kernel.c" -o kernel_asm.S $CFLAGS

# 🔹 Link everything
$CC $TARGET $LDFLAGS -o myos.bin $OBJ_FILES

# 🔹 GRUB image
mkdir -p ./boot/grub
cp myos.bin ./boot/myos.bin
cp "$PROJECT_ROOT/grub.cfg" ./boot/grub/grub.cfg
grub-mkrescue -o myos.iso .