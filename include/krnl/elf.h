#include <mod.h>

typedef struct elf32head {
    uint32_t e_magic;

    uint8_t e_arch;
    uint8_t e_endian;
    uint8_t e_version;
    uint8_t e_abi;
    uint8_t e_abiv;
    uint8_t e_pad[7];

    uint16_t e_type;
    uint16_t e_machine;

    uint32_t e_version2;
    uint32_t e_entry;
    uint32_t e_phoff;
    uint32_t e_shoff;
    uint32_t e_flags;
    
    uint16_t e_ehsize;
    uint16_t e_phentsize;
    uint16_t e_phnum;
    uint16_t e_shentsize;
    uint16_t e_shnum;
    uint16_t e_shstrndx;
} elf32head_t;

typedef struct elf32prog {
    uint32_t e_type;
    uint32_t e_offset;
    uint32_t e_vaddr;
    uint32_t e_paddr;
    uint32_t e_filesz;
    uint32_t e_memsz;
    uint32_t e_flags;
    uint32_t e_align;
} elf32prog_t;

#if ARCH_BITS == 32
#define ELF_LOADER elf32_loader
#endif

int elf32_loader(uint8_t *prog);
