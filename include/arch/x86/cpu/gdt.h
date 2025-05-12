#pragma once
#include <arch/x86/x86.h>

typedef struct gdt_entry {
    uint16_t e_lim_low;
    uint16_t e_base_low;
    uint8_t e_base_middle;
    uint8_t e_access;
    uint8_t e_length;
    uint8_t e_base_high;
} __attribute__((packed)) gdt_entry_t;

typedef struct gdt_pointer {
    uint16_t p_size;
    uint32_t p_addr;
} __attribute__((packed)) gdt_pointer_t;

typedef struct tss {
    uint32_t t_prev;
    uint32_t t_esp0;
    uint32_t t_ss0;
    uint32_t t_unused[23];
} __attribute__((packed)) tss_t;

extern tss_t TSS;

extern gdt_entry_t gdt_entries[];
extern gdt_pointer_t gdt_ptr;

void gdt_init();
void gdt_load();
void gdt_set(uint32_t base, uint32_t limit);
void gdt_entry_set(uint8_t index, uint32_t base, uint32_t limit, uint8_t access, uint8_t len);
