#include <bosykrnl/kernel.h>

struct int86regs {
    uint16_t ax, bx, cx, dx, si, di, ds, es, flags;
};

extern uint32_t int86(int inum, struct int86regs *regs);
