import os
from pathlib import Path
import subprocess
from termcolor import colored
import sys
import re  # For removing |...| wrapped strings

# Paths and configuration
GRUB_CFG = "grub.cfg"
BOOT_DIR = Path("build/output/boot")
PROJECT_ROOT = Path("../..")
COMPILATION_SCRIPT = Path("./scripts/qemu/runOs_qemu.sh")
OUTPUT_FILE = Path("build/output/out")


def set_grub_default(entry_index):
    """Modify GRUB to boot a specific entry by default."""
    with open(GRUB_CFG, "r+") as grub_file:
        lines = grub_file.readlines()
        updated_lines = []
        for line in lines:
            if line.strip().startswith("set default="):
                updated_lines.append(f"set default={entry_index}\n")
            elif line.strip().startswith("set timeout="):
                updated_lines.append("set timeout=0\n")
            else:
                updated_lines.append(line)
        if not any(line.strip().startswith("set default=") for line in updated_lines):
            updated_lines.insert(0, f"set default={entry_index}\n")
        if not any(line.strip().startswith("set timeout=") for line in updated_lines):
            updated_lines.insert(1, "set timeout=0\n")
        grub_file.seek(0)
        grub_file.writelines(updated_lines)
        grub_file.truncate()


def pretty_print_result(result_code, message):
    """Pretty print test results in green (success) or red (failure)."""
    if result_code == "1":
        print(colored("✔️  SUCCESS: ", "green") + message)
    else:
        print(colored("❌ FAILURE: ", "red") + message)


def read_test_result():
    """Read test result from OUTPUT_FILE, removing |...| wrapped segments."""
    if OUTPUT_FILE.exists():
        with open(OUTPUT_FILE, "r") as f:
            lines = f.readlines()
            if len(lines) >= 2:
                result_code = re.sub(r'\|.*?\|', '', lines[0]).strip()
                message = re.sub(r'\|.*?\|', '', lines[1]).strip()
                return result_code, message
            else:
                return None, "Incomplete test output."
    else:
        return None, "Output file not found."


def add_test_and_compile(category, testname, entry_index):
    """Add a GRUB entry, compile a test, and interpret its results."""
    test_bin = f"{category}/{testname}/{testname}.bin"
    test_main = PROJECT_ROOT / f"tests/{category}/{testname}/{testname}.c"
    test_kernel = PROJECT_ROOT / f"tests/{category}/{testname}/{testname}Kernel.c"

    # Add GRUB entry
    with open(GRUB_CFG, "a") as grub_file:
        grub_file.write(f"\nmenuentry \"{category} - {testname}\" {{\n")
        grub_file.write(f"    multiboot /boot/{test_bin}\n")
        grub_file.write("    set gfxpayload=text\n")
        grub_file.write("    boot\n")
        grub_file.write("}\n")

    # Set GRUB to boot this entry
    set_grub_default(entry_index)

    # Compile the test
    print(f"Compiling test: {category}/{testname}")
    command = [str(COMPILATION_SCRIPT), str(test_kernel), str(test_main), test_bin]
    result = subprocess.run(command, capture_output=True, text=True)

    # Read test results
    print("Running test...")
    result_code, message = read_test_result()
    if result_code:
        pretty_print_result(result_code, message)
        return result_code == "1"
    else:
        print(colored("⚠️ WARNING: No result found.", "yellow") + f" Message: {message}")
        return False


def main():
    """Main entry point for the script."""
    all_tests_successful = True

    with open(GRUB_CFG, "w") as grub_file:
        grub_file.write(
            """menuentry "myos" {
    multiboot /boot/myos.bin
    set gfxpayload=1920x1080x32
    boot
}

menuentry "vga text mode os" {
    multiboot /boot/myos.bin
    set gfxpayload=text
}
"""
        )

    BOOT_DIR.mkdir(parents=True, exist_ok=True)

    tests_dir = Path("tests")
    test_index = 2
    for category_path in tests_dir.iterdir():
        if category_path.is_dir():
            category = category_path.name
            for test_path in category_path.iterdir():
                if test_path.is_dir():
                    testname = test_path.name
                    success = add_test_and_compile(category, testname, test_index)
                    test_index += 1
                    if not success:
                        all_tests_successful = False
                        print(colored(f"Skipping test {category}/{testname} due to errors.", "yellow"))

    print("GRUB configuration and compilation completed successfully!")

    # Set the return code
    if all_tests_successful:
        sys.exit(0)  # All tests successful
    else:
        sys.exit(-1)  # At least one test failed


if __name__ == "__main__":
    main()
