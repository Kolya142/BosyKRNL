#include <arch/x86/cpu/idt.h>

INT_DEF(idt_nothing) {
}

#define IDT_TABLE_SIZE 256

idtr_t idtr;
idt_descriptor_t idt_table[IDT_TABLE_SIZE];

void idt_set(uint8_t i, void *p, uint8_t select, uint8_t f) {
    idt_descriptor_t *d = &idt_table[i];
    d->low    = (uint32_t)p & 0xFFFF;
    d->high   = (uint32_t)p >> 16;

    d->select = select;
    d->zero   = 0;

    d->attr = f;
}

void idt_init() {
    idtr.base = (uint32_t)idt_table;
    idtr.lim  = (uint16_t)(sizeof(idt_descriptor_t) * IDT_TABLE_SIZE - 1);
    for (uint16_t i = 0; i < IDT_TABLE_SIZE; ++i) {
        idt_set(i, idt_nothing, 0x08, 0x8E);
    }
    __asm__ volatile(
        "lidt %0\n"
        "sti" : : "m"(idtr)
    );
}
