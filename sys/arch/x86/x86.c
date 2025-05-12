#include <arch/x86/cpu/gdt.h>
#include <arch/x86/cpu/idt.h>
#include <arch/x86/cpu/pic.h>
#include <arch/x86/x86.h>

void outb(uint16_t port, uint8_t data) {
    __asm__ __volatile__("outb %0, %1" : : "a"(data), "Nd"(port));
}
uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
void outw(uint16_t port, uint16_t data) {
    __asm__ __volatile__("outw %0, %1" : : "a"(data), "Nd"(port));
}
uint16_t inw(uint16_t port) {
    uint16_t ret;
    __asm__ __volatile__("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
void outd(uint16_t port, uint32_t data) {
    __asm__ __volatile__("out %0, %1" : : "a"(data), "Nd"(port));
}
uint32_t ind(uint16_t port) {
    uint32_t ret;
    __asm__ __volatile__("in %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

void cpu_init() {
    gdt_init();
    idt_init();
    pic_set();
}
