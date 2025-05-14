#pragma once
#include <stdint.h>

#define ARCH_I386 0
#define ARCH_AMD64 1
#define ARCH_ARM32 2
#define ARCH_AARCH64 3
#define ARCH_RISCV32 4
#define ARCH_RISCV64 5

#if !defined(ARCH)
#define ARCH ARCH_I386
#endif

#if ARCH == ARCH_I386
#define ARCH_BITS 32
#define ARCH_BYTES 4
typedef uint32_t uintarch_t;
#elif ARCH == ARCH_AARCH64
#define ARCH_BITS 64
#define ARCH_BYTES 8
typedef uint64_t uintarch_t;
#endif

#define NULL 0
#define FALSE 0
#define TRUE 1

void kmemcpy(void *dst, void *src, uintarch_t len);
void kmemset(void *dst, uint8_t val, uintarch_t len);

uintarch_t kstrlen(const char *s);
int kstrcmp(const char *a, const char *b);
