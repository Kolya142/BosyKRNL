int entry(int argc, char **argv, char **environ, char *libc_ver);

#define NULL 0

int _start() {
    return entry(0, NULL, NULL, "0.0.1");
}
