void exit(int code);
int entry(int argc, char **argv, char **environ, char *libc_ver);

#define NULL 0

void _start() {
    int code = entry(0, NULL, NULL, "0.0.1");
    exit(code);
}
