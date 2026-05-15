# multiboot.h

## Description
The header file defining structures and magic numbers required for Multiboot specification compliance.

## Types
- `multiboot_header_t`
- `aout_symbol_table_t`
- `elf_section_header_table_t`
- `multiboot_info_t`: Crucial structure passed by GRUB containing memory map, VBE info, etc.
- `module_t`
- `memory_map_t`
