#include <bosykrnl/arch/x86/cpu/int.h>

extern void int86_trampoline();

uint32_t int86(int inum, struct int86regs *regs) {
    /*
    extern uint8_t _int86_inum;
    extern struct int86regs _int86_regs;

    _int86_inum = inum;
    _int86_regs = *regs;

    int86_trampoline();

    *regs = _int86_regs;
    */
    return regs->ax;
}
