#include <arch/x86/cpu/gdt.h>

tss_t tss;

gdt_entry_t gdt_entries[6];
gdt_pointer_t gdt_ptr;

void gdt_init() {
    gdt_ptr.p_size = (sizeof(gdt_entry_t) * 6) - 1;
    gdt_ptr.p_addr = (uint32_t)&gdt_entries;
    kmemset(&tss, 0, sizeof(tss));

    gdt_entry_set(0, 0, 0, 0, 0);
    gdt_entry_set(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_entry_set(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    gdt_entry_set(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
    gdt_entry_set(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);
    gdt_entry_set(5, (uint32_t)&tss, sizeof(tss), 0x89, 0x40);

    tss.t_esp0 = 0x200000;
    tss.t_ss0 = 0x10;

    gdt_load();
    asm(
	"movw $0x28, %%ax\n"
	"ltr %%ax"
	::: "eax"
    );
}
void gdt_load() {
    asm(
        "lgdt %0\n"
        "movw $0x10, %%ax\n"
        "movw %%ax, %%ds\n"
        "movw %%ax, %%es\n"
        "movw $0,   %%ax\n"
        "movw %%ax, %%fs\n"
        "movw %%ax, %%gs\n"
        "jmpl $0x08, $.cs_reload\n" // Replace with "jmpf" if your system doen't support jmp flags
        ".cs_reload:\n"
        :: "m"(gdt_ptr)
        : "eax"
    );
}
void gdt_set(uint32_t base, uint32_t limit) {
    gdt_entry_set(3, base, limit, 0xFA, 0xCF);
    gdt_entry_set(4, base, limit, 0xF2, 0xCF);
}
void gdt_entry_set(uint8_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t len) {
    gdt_entries[index].e_base_low = (base & 0xFFFF);
    gdt_entries[index].e_base_middle = (base >> 16) & 0xFF;
    gdt_entries[index].e_base_high = (base >> 24) & 0xFF;
    gdt_entries[index].e_lim_low = (limit & 0xFFFF);
    gdt_entries[index].e_length = ((limit >> 16) & 0x0F) | (len & 0xF0);
    gdt_entries[index].e_access = access;
}
