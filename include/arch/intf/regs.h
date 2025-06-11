#pragma once
#include <kernel.h>

#if ARCH == ARCH_I386
#include <arch/x86/cpu/idt.h>
typedef int_regs3_t regs_t;
#endif
