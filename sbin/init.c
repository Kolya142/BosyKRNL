#include <unistd.h>
#include <string.h>

int entry(int argc, char **argv, char **environ, char *ver) {
    bool lk[256];
    for (int i = 0; i < 256; ++i) {
	lk[i] = FALSE;
    }
    char buf[1024];
    int bufi = 0;
    debug_print("$ ");
    for (;;) {
	for (byte_t key = 0; key < 128; ++key) {
	    if (is_pressed(key)) {
		if (!lk[key]) {
		    lk[key] = TRUE;
		    if (key == '\r') {
			debug_print("\n");
			buf[bufi] = 0;
			bufi = 0;
			if (!strcmp(buf, "help")) {
			    debug_print("help clear echo demo\n");
			}
			else if (!strcmp(buf, "demo")) {
			    execv("demo");
			}
			else if (!strcmp(buf, "clear")) {
			    debug_print("\x1b[2J\x1b[H");
			}
			else if (buf[0] == 'e' && buf[1] == 'c' && buf[2] == 'h' && buf[3] == 'o') {
			    debug_print(buf+5);
			    debug_print("\n");
			}
			debug_print("$ ");
		    }
		    else if (key == '\b') {
			if (bufi) {
			    debug_print("\b \b");
			    buf[--bufi] = 0;
			}
		    }
		    else {
			if (bufi < sizeof(buf)) {
			    debug_print((char[]) {key, 0});
			    buf[bufi++] = key;
			}
		    }
		}
	    }
	    else {
		lk[key] = FALSE;
	    }
	}
    }
}
