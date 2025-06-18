// FIXME
#include "bosykrnl/arch/intf/regs.h"
#include <bosykrnl/arch/x86/cpu/paging.h>
#include <bosykrnl/arch/x86/cpu/pit.h>
#include <bosykrnl/krnl/shred.h>

uint32_t pit_ticks = 0;

static void map_pages(task_t *task) {
    for (int i = 0; i < task->pages.count; ++i) {
	page_t *page = vector_get(&task->pages, i);
	/*
	kputsa("MAPPING ");
	kputha(page->real);
	kputsa(" AS ");
	kputha(page->virt);
	kputsa("\n");
	*/
	// FIMXE
	paging.map_page(page->real, page->virt, 7);
    }
}

static INT_DEF(pit_irq_handler) {
    ++pit_ticks;
    if (task_first && can_tasking) {
	bool is_dead = task_curr->state == TASK_DEAD;
	if (is_dead) {
	    task_t *task = task_curr;
	    task_next();
	    kfree(task);
	}
	if (task_curr->state != TASK_READY) {
	    if (!is_dead) {
		if (regs->ds & 3)
		    kmemcpy(&task_curr->regs, regs, sizeof(regs_t));
		else
		    kmemcpy(&task_curr->regs, regs, sizeof(regs_kernel_t));
	    }
	}
	else {
	    kputsa("ready!");
	    task_curr->state = TASK_RUNNING;
	}
	task_next();
	if(!task_curr->is_kernel)
	    kmemcpy(regs, &task_curr->regs, sizeof(regs_t));
	else
	    kmemcpy(regs, &task_curr->regs, sizeof(regs_kernel_t));
	map_pages(task_curr);
    }
}

void pit_init() {
    idt_set(32, pit_irq_handler, 0x08, 0x8E);

    int div = 1193182 / 1000;
    outb(0x43, 0x36);
    outb(0x40, div & 0xFF);
    outb(0x40, (div >> 8) & 0xFF);
    outb(0x21, inb(0x21) & ~1);
}
