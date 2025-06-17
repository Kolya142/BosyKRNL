#include <bosykrnl/krnl/syscalls.h>
#include <bosykrnl/dev/keyboard.h>
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
    }
}

void syscalls_init() {
#if ARCH == ARCH_I386
    idt_set(0x80, syscall_handler, 0x08, 0xEE);
#endif
}
