#pragma once
#include <stddef.h>

#define ARCH_I386 0
#define ARCH_X86_64 1
#define ARCH_ARM32 2
#define ARCH_AARCH64 3
#define ARCH_RISCV32 4
#define ARCH_RISCV64 5
#define ARCH_MIPS64EL 6

#if !defined(ARCH)
#define ARCH ARCH_I386
#endif

#if ARCH == ARCH_I386
#define ARCH_BITS 32
#define ARCH_BYTES 4
#elif ARCH == ARCH_AARCH64
#define ARCH_BITS 64
#define ARCH_BYTES 8
#endif

extern bool can_tasking;

void kmemcpy(void *dst, void *src, uintarch_t len);
void kmemset(void *dst, uint8_t val, uintarch_t len);

int kstrcmp(const char *a, const char *b);
uintarch_t kstrlen(const char *s);

int kputsa(const char *s);
int kputha(uintarch_t d);

void kheap_init();
bool kheap_check();
void *kmalloc(uintarch_t count);
void kfree(void *ptr);
