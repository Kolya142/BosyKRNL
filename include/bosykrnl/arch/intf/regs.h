#pragma once
#include <bosykrnl/kernel.h>

#if ARCH == ARCH_I386
#include <bosykrnl/arch/x86/cpu/idt.h>
typedef int_regs3_t regs_t;
typedef int_regs_t regs_kernel_t;
#endif
