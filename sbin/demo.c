#include <unistd.h>
#include <string.h>

int entry(int argc, char **argv, char **environ, char *ver) {
    char c = 0;
    int a = 0;
    int b = 0xA938B4F;
    for (int i = 0; i < 10; ++i) {
	b += a * 0xF0AD83 + b - 0xAB20;
	c += a - b;
	--a;
	debug_print((char[]) {c, a, b, 0});
    }
    return 0;
}
