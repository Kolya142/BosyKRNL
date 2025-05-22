#include "kernel.h"
#include <mod.h>

void kmemcpy(void *dst, void *src, uintarch_t len){
#if (ARCH == ARCH_I386) || (ARCH == ARCH_AMD64)
    asm volatile("cld\n"
                 "rep movsb" ::
		 "c"(len), "S"(src), "D"(dst) : "memory");
#endif
}


void kmemset(void *dst, uint8_t val, uintarch_t len) {
#if (ARCH == ARCH_I386) || (ARCH == ARCH_AMD64)
    asm volatile("cld\n"
                 "rep stosb" ::
		 "c"(len), "a"(val), "D"(dst) : "memory");
#endif
}

// FIXME
void memcpy(void *d, void *s, uintarch_t l) {kmemcpy(d, s, l);}

int kstrcmp(const char *a, const char *b) {
    while (*a && *b) {
	++a;
	++b;
    }
    return *a - *b;
}

uintarch_t kstrlen(const char *s) {
    uintarch_t a = 0;
    while (*s) {++s; ++a;}
    return a;
}

// PUT String Anywere
int kputsa(const char *s) {
    for (int i = 0; i < MODSC; ++i) {
	if (mods[i]->flags & MOD_FLAGS_CHAROUT) {
	    mods[i]->write(&devs[i], 0, s, kstrlen(s));
	    return 1;
	}
    }
    return 0;
}

int kputha(uintarch_t d) {
    if (!d) {
	return kputsa("0");
    }
    char buf[64];
    buf[63] = 0;
    int i = 62;
    while (d) {
	buf[i] = "0123456789ABCDEF"[d % 16];
        --i;
	d /= 16;
    }
    return kputsa(buf + i + 1);
}
