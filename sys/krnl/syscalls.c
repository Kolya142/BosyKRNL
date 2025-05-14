#include <krnl/syscalls.h>
#if ARCH == ARCH_I386
#include <arch/x86/cpu/idt.h>
#endif

static INT_DEF(syscall_handler) {
    switch (regs->eax) {
    case 0:
	
    }
}

void syscalls_init() {
    idt_set(0x80, syscall_handler, 0x08, 0xEE);
}
