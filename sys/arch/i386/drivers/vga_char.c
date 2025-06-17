#include <bosykrnl/arch/x86/drivers/vga_char.h>
#include <bosykrnl/arch/x86/x86.h>

static uint32_t c, fg, bg;

static void vga_load(dev_t *dev) {
    c = 0;
    fg = 0x0F;
    bg = 0x00;
}

static void vga_cursor_set(uint32_t c)
{
    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t) (c & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t) ((c >> 8) & 0xFF));
}

static uintarch_t vga_write(dev_t *dev, FS_RW_ARGS) {
    char *cbuf = buf;
    uintarch_t i;
    for (i = 0; i < count; ++i) {
	if (cbuf[i] == '\n') {
	    c -= c % 80;
	    c += 80;
	}
	else if (cbuf[i] == '\t') {
	    c -= c % 4;
	    c += 4;
	}
	else if (cbuf[i] == '\b') {
	    --c;
	}
	else if (cbuf[i] == '\x1b') {
	    ++i;
	    int nums[10];
	    kmemset(nums, 0, sizeof(nums));
	    int numi = 0;
	    if (cbuf[i] == '[') {
		++i;
		do {
		    while (cbuf[i] >= '0' && cbuf[i] <= '9') {
			nums[numi] *= 10;
			nums[numi] += cbuf[i] - '0';
			++i;
		    }
		    if (cbuf[i] == ';') {
			++i;
			++numi;
		    }
		} while (cbuf[i] == ';');
		switch (cbuf[i]) {
		case 'J': {
		    if (nums[0] == 2) {
			for (uint32_t j = 0; j < 80 * 25; ++j) {
			    ((short*)0xB8000)[j] = 0;
			}
		    }
		    break;
		}
		case 'H': {
		    if (!nums[0]) nums[0] = 1;
		    if (!nums[1]) nums[1] = 1;
		    c = (nums[0]-1)+80*(nums[1]-1);
		    break;
		}
		case 'K': {
		    for (uint32_t j = c; j < c + (80 - (c % 80)); ++j) {
			((short*)0xB8000)[j] = 0;
		    }
		    break;
		}
		}
	    }
	}
	else {
	    ((short*)0xB8000)[c] = ((fg | (bg << 4)) << 8) | (uint8_t)cbuf[i];
	    ++c;
	}
	if (c >= 80*25) {
	    kmemcpy((void *)0xB8000, (void *)0xB8000 + 80*2, 80*24*2);
	    for (uint32_t i = 80 * 24; i < 80 * 25; ++i) {
		((short*)0xB8000)[i] = 0;
	    }
	    c = 80*24;
	}
    }
    vga_cursor_set(c);
    return i;
}

static uintarch_t vga_ioctl(dev_t *dev, uintarch_t fd, uint32_t type, uintarch_t a, uintarch_t _b, uintarch_t _c, uintarch_t _d) {
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
