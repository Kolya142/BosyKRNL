#pragma once
#include <kernel.h>

extern void (*syscalls[])();

void syscalls_init();
