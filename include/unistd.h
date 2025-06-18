#pragma once
#include <stddef.h>

void debug_print(const char *s);
bool is_pressed(byte_t key);
long execv(const char *file);
void exit(int code);
void nice(int value);
