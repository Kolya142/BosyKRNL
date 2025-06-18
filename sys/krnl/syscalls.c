#include <bosykrnl/krnl/shred.h>
#include <bosykrnl/krnl/syscalls.h>
#include <bosykrnl/krnl/elf.h>
#include <bosykrnl/dev/keyboard.h>
#include <bosykrnl/fs/iso9660.h>
#include <errno.h>
#if ARCH == ARCH_I386
#include <bosykrnl/arch/x86/cpu/idt.h>
#endif

static INT_DEF(syscall_handler) {
    switch (regs->eax) {
    case 0: {
        kputsa((char *)regs->ebx);
	regs->eax = 0;
	break;
    }
    case 1: {
	if (regs->ebx > 255) {
	    regs->eax = ENOENT;
	    break;
	}
	regs->eax = keyboard.keys[regs->ebx];
	break;
    }
    case 2: {
	struct stat elf_stat;
	if (!iso9660fs.stat(&devs[1], mods[1], (const char *)regs->ebx, &elf_stat)) {
	    regs->eax = 1;
	    break;
        }
    
	byte_t *elf = kmalloc(elf_stat.size);
	// kputha((uintptr_t)elf);
	iso9660fs.read(&devs[1], mods[1], 0, (const char *)regs->ebx, elf, elf_stat.size);
	
	regs->eax = elf32_loader(elf);

	kfree(elf);
	break;
    }
    case 3: {
	task_kill(task_curr->id);

	// Unreachable in userland
	break;
    }
    case 4: {
	regs->eax = task_curr->id;
	break;
    }
    case 5: {
	task_curr->priority = regs->ebx;

	regs->eax = 0;
	break;
    }
    }
}

void syscalls_init() {
#if ARCH == ARCH_I386
    idt_set(0x80, syscall_handler, 0x08, 0xEE);
#endif
}
