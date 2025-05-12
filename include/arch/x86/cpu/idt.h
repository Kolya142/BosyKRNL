#pragma once
#include <arch/x86/x86.h>


typedef struct idt_descriptor {
    uint16_t low;
    uint16_t select;
    uint8_t  zero;
    uint8_t  attr;
    uint16_t high;
} __attribute__((packed)) idt_descriptor_t;
typedef struct idtr {
    uint16_t lim;
    uint32_t base;
} __attribute__((packed)) idtr_t;
void idt_set(uint8_t i, void *p, uint8_t select, uint8_t f);

void idt_init();

typedef struct int_regs {
    uint32_t edi, esi, ebp, useresp, ebx, edx, ecx, eax;
    uint32_t eflagsp;
    uint32_t ds, es, gs, fs;
    uint32_t eip, cs, eflags;
} __attribute__((packed)) int_regs_t;
typedef struct int_regs3 { // Same but with ss/esp
    uint32_t edi, esi, ebp, useresp, ebx, edx, ecx, eax;
    uint32_t eflagsp;
    uint32_t ds, es, gs, fs;
    uint32_t eip, cs, eflags;
    uint32_t esp, ss;
} __attribute__((packed)) int_regs3_t;
#define INT_DEF(fn) \
    __attribute__((naked)) void fn() { \
        asm("cli\n" \
            "push %fs\n" \
            "push %gs\n" \
            "push %es\n" \
            "push %ds\n" \
            "pushf\n" \
            "pushal\n" \
                       \
            "mov $0x10, %ax\n" \
            "mov %ax, %ds\n" \
            "mov %ax, %es\n" \
            "mov %ax, %fs\n" \
            "mov %ax, %ss\n" \
                       \
            "movl %esp, %eax\n" \
            "pushl %eax\n" \
            "call "#fn"_impl\n" \
            "addl $4, %esp\n" \
                            \
            "movb $0x20, %al;\n" \
            "outb %al, $0x20\n" \
                            \
            "movb $0x20, %al;\n" \
            "outb %al, $0xA0\n" \
            \
            "popal\n" \
            "popf\n" \
            "pop %ds\n" \
            "pop %es\n" \
            "pop %gs\n" \
            "pop %fs\n" \
            "iret\n"); \
    } \
    void fn##_impl(int_regs3_t *regs)
