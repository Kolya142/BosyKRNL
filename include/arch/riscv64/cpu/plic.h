#pragma once
#include <stdint.h>

#define PLIC_BASE         0x0C000000
#define PLIC_PRIORITY     (PLIC_BASE + 0x000000)
#define PLIC_PENDING      (PLIC_BASE + 0x001000)
#define PLIC_ENABLE       (PLIC_BASE + 0x002000)
#define PLIC_CONTEXT_BASE (PLIC_BASE + 0x200000)

#define PLIC_CONTEXT(hart, mode) ((hart << 1) | (mode))
#define PLIC_ENABLE_OFFSET(context) (PLIC_ENABLE + 0x80 * context)
#define PLIC_THRESHOLD(context)     (PLIC_CONTEXT_BASE + 0x1000 * context + 0x0)
#define PLIC_CLAIM(context)         (PLIC_CONTEXT_BASE + 0x1000 * context + 0x4)

void plic_init(uint32_t context);
void plic_enable_irq(uint32_t context, uint32_t irq);
void plic_set_priority(uint32_t irq, uint32_t prio);
void plic_set_threshold(uint32_t context, uint32_t threshold);
uint32_t plic_claim(uint32_t context);
void plic_complete(uint32_t context, uint32_t irq);
