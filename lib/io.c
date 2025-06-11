#include <unistd.h>

void debug_print(const char *s) {
    asm __HARDWARE (
	"xor %%eax, %%eax\n"
	"mov %0, %%ebx\n"
	"int $0x80"
	:: "r"(s)
	: "eax", "ebx"
    );
}

bool is_pressed(byte_t key) {
    char res;
    asm __HARDWARE (
	"movl $1, %%eax\n"
	"xor %%ebx, %%ebx\n"
	"movb %0, %%bl\n"
	"int $0x80\n"
	"movb %%al, %1\n"
	: "=r"(res)
	: "r"(key)
	: "eax", "ebx"
    );
    return res;
}

int strcmp(char *a, char *b) {
    while (*a == *b && *a && *b) {++a;++b;}
    return *a - *b;
}

int strncmp(char *a, char *b, int c) {
    while (*a == *b && *a && *b && c) {++a;++b;++c;}
    return *a - *b;
}
