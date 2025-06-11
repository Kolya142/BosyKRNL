#pragma once
#include <stdint.h>

#define __USER
#define __KERNEL
#define __SAFE
#define __NOCAST
#define __IOMEM
#define __NULLABLE
#define __NONULL
#define __UNSAFE

#define __HARDWARE volatile
#define __NOOPTIMIZE volatile __attribute__((noinline)) __attribute__((used))
#define __NORETURN __attribute__((noreturn))
#define __PACKED __attribute__((packed))
#define __ALIGN(x) __attribute__((aligned(x)))
#define __UNUSED __attribute__((unused))
#define __WEAK __attribute__((weak))

#undef NULL
#undef FALSE
#undef TRUE

#define NULL 0
#define FALSE 0
#define TRUE 1

#undef I8_MIN
#undef I8_MAX
#undef U8_MIN
#undef U8_MAX
#undef I16_MIN
#undef I16_MAX
#undef U16_MIN
#undef U16_MAX
#undef I32_MIN
#undef I32_MAX
#undef U32_MIN
#undef U32_MAX
#undef I64_MIN
#undef I64_MAX
#undef U64_MIN
#undef U64_MAX

#define I8_MIN (-0x80)
#define I8_MAX 0x7F
#define U8_MIN 0
#define U8_MAX 0xFF
#define I16_MIN (-0x8000)
#define I16_MAX 0x7FFF
#define U16_MIN 0
#define U16_MAX 0xFFFF
#define I32_MIN (-0x80000000)
#define I32_MAX 0x7FFFFFFF
#define U32_MIN 0
#define U32_MAX 0xFFFFFFFF
#define I64_MIN (-0x8000000000000000)
#define I64_MAX 0x7FFFFFFFFFFFFFFF
#define U64_MIN 0
#define U64_MAX 0xFFFFFFFFFFFFFFFF
