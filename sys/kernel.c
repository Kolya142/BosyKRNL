#include <kernel.h>

void kmemcpy(void *dst, void *src, uintarch_t len){
#if (ARCH == ARCH_I386) || (ARCH == ARCH_AMD64)
    asm volatile("cld\n"
                 "rep movsb" ::"c"(len),
                 "S"(src), "D"(dst) : "memory");
#endif
}


void kmemset(void *dst, uint8_t val, uintarch_t len) {
#if (ARCH == ARCH_I386) || (ARCH == ARCH_AMD64)
    asm volatile("cld\n"
                 "rep stosb" ::
		 "c"(len), "a"(val), "D"(dst) : "memory");
#endif
}

int kstrcmp(const char *a, const char *b) {
    while (*a && *b) {
	++a;
	++b;
    }
    return *a - *b;
}
