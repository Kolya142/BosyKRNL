#include "mod.h"
#include <arch/x86/drivers/vga_char.h>

static uint32_t c, fg, bg;

static void vga_load(dev_t dev) {
    c = 0;
    fg = 0x0F;
    bg = 0x00;
}

static uintarch_t vga_write(dev_t dev, FS_RW_ARGS) {
    char *cbuf = buf;
    uintarch_t i;
    for (i = 0; i < count; ++i) {
      ((short*)0xB8000)[c] = ((fg | (bg << 4)) << 8) | (uint8_t)cbuf[i];
	if (c >= 80*25) break;
	++c;
    }
    return i;
}

static uintarch_t vga_ioctl(dev_t dev, uintarch_t fd, uint32_t type, uintarch_t a, uintarch_t, uintarch_t, uintarch_t) {
    if (type == IO_CURSET) {
	c = a;
	return 0;
    }
    return 1;
}

mod_t mod_vga_char = {
    .load = vga_load,
    .write = vga_write,
    .ioctl = vga_ioctl,
    .flags = MOD_FLAGS_CHAROUT
};
