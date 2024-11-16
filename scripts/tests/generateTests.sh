#!/bin/bash

# Paths and configuration
GRUB_CFG="grub.cfg"
BOOT_DIR="build/output/boot"
PROJECT_ROOT="../.."
COMPILATION_SCRIPT="./scripts/qemu/runOs_qemu.sh"

# Start with default GRUB menu entries
cat > "$GRUB_CFG" <<EOL
menuentry "myos" {
	multiboot /boot/myos.bin
    set gfxpayload=1920x1080x32
	boot
}

menuentry "vga text mode os" {
	multiboot /boot/myos.bin
	set gfxpayload=text
}
EOL

# Function to add test entries and compile tests
add_test_and_compile() {
    local category="$1"
    local testname="$2"
    local test_bin="$category/$testname/$testname.bin"
    local test_main="$PROJECT_ROOT/tests/$category/$testname/$testname.c"
    local test_kernel="$PROJECT_ROOT/tests/$category/$testname/${testname}Kernel.c"

    # Add GRUB entry
    echo >> "$GRUB_CFG"
    echo "menuentry \"$category - $testname\" {" >> "$GRUB_CFG"
    echo "    multiboot /boot/$test_bin" >> "$GRUB_CFG"
    echo "    set gfxpayload=text" >> "$GRUB_CFG"
    echo "    boot" >> "$GRUB_CFG"
    echo "}" >> "$GRUB_CFG"

    # Compile the test
    echo "Compiling test: $category/$testname"
    bash "$COMPILATION_SCRIPT" "$test_kernel" "$test_main" "$test_bin"
}

# Ensure BOOT_DIR exists
mkdir -p "$BOOT_DIR"

# Scan for test directories and compile
find "tests" -mindepth 2 -maxdepth 2 -type d | while read -r test_dir; do
    # Extract category and testname
    category=$(basename "$(dirname "$test_dir")")
    testname=$(basename "$test_dir")

    # Add entry and compile
    add_test_and_compile "$category" "$testname"
done

echo "GRUB configuration and compilation completed successfully!"