#include <arch/x86/cpu/pit.h>
#include <krnl/shred.h>

uint32_t pit_ticks = 0;

static INT_DEF(pit_irq_handler) {
    ++pit_ticks;
    if (task_first) {
	kmemcpy(task_curr, regs, sizeof(regs));
	task_next();
	kmemcpy(regs, task_curr, sizeof(regs));
    }
}

void pit_init() {
    idt_set(32, pit_irq_handler, 0x08, 0x8E);

    int div = 1193182 / 100;
    outb(0x43, 0x36);
    outb(0x40, div & 0xFF);
    outb(0x40, (div >> 8) & 0xFF);
    outb(0x21, inb(0x21) & ~1);
}
