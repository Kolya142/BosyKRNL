int entry(int argc, char **argv, char **environ, char *ver) {
    asm (
	"xor %%eax, %%eax;"
	"mov %0, %%ebx;"
	"int $0x80"
	:: "r"("LIBC: ")
	: "eax", "ebx"
    );
    asm (
	"xor %%eax, %%eax;"
	"mov %0, %%ebx;"
	"int $0x80"
	:: "r"(ver)
	: "eax", "ebx"
    );
}
