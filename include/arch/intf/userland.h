#include <kernel.h>

#if ARCH == ARCH_I386
extern __attribute__((cdecl, noreturn, naked)) void x86_ring3_switch(uint32_t entry, uint32_t stack);

#define SWITCH_TO_USERLAND x86_ring3_switch
#endif
