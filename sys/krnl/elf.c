#include <krnl/elf.h>

int elf32_loader(uint8_t *prog) {
    elf32head_t *elf = (elf32head_t *)prog;
    if (elf->e_magic != 0x464C457F) {
	return -1;
    }
    if (elf->e_arch != 1 || elf->e_machine != 3) {
        return 2;
    }

    elf32prog_t *ph = (elf32prog_t*)(prog + elf->e_phoff);
    for (uint32_t i = 0; i < elf->e_phnum; ++i, ++ph) {
	if (ph->e_type != 1) continue;

	for (uint32_t off = 0; off < ph->e_memsz; off += 0x1000) {
	    void *poff = (void*)ph->e_vaddr + off;

	    if (off < ph->e_filesz) {
		uint32_t len = 0x1000;
		if (ph->e_filesz - off < len) len = ph->e_filesz - off;
		kmemcpy(poff, prog + ph->e_offset + off, len);

		if (len < 0x1000 && ph->e_memsz > ph->e_filesz) {
		    kmemset(poff + len, 0, 0x1000 - len);
		}
	    }
	    else {
		kmemset(poff, 0, 0x1000);
	    }
	}
    }
    void(*ent)() = (void *)elf->e_entry;
    ent();
    return 0;
}
