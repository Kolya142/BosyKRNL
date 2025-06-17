#pragma once

#include <bosykrnl/arch/x86/drivers/ps2.h>
#include <bosykrnl/arch/x86/cpu/idt.h>
#include <bosykrnl/dev/keyboard.h>

void keyboard_init();
