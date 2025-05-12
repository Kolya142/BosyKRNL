#include "kernel.h"
#include "mod.h"
#include <arch/x86/drivers/ide.h>

static uintarch_t cursor1 = 0;

static void init1() {}
static uintarch_t read1(dev_t dev, FS_RW_ARGS) {
    if (count % 512 != 0) return 0;
    count /= 512;
    uint32_t count1 = 0;
    while (count) {
	uint32_t lba = cursor1 * 512;
	outb(0x01F6, 0xE0 | ((lba >> 24) & 15));
	outb(0x01F2, count);
	outb(0x01F3, lba & 0xFF);
	outb(0x01F4, ((lba >> 8)) & 0xFF);
	outb(0x01F5, ((lba >> 16)) & 0xFF);
	outb(0x01F7, 0x20);

	uint32_t timeout = 1000000;
	while (inb(0x01F7) & 0x80 && --timeout);
	if (!timeout) break;

	if (inb(0x01F7) & 1) break;

	uint8_t *buf8 = buf;

        timeout = 1000000;
	while (!(inb(0x01F7) & 0x08)) {
	    if (inb(0x01F7) & 1) { break; }
	    if (!--timeout) { break; }
	}

	for (uint32_t i = 0; i < 256; ++i) {
	    uint16_t word = inb(0x01F0);
            buf8[i * 2] = word & 0xff;
            buf8[i * 2 + 1] = (word >> 8) & 0xff;
	}
	
	buf += 512;
	--count;
	++count1;
        ++cursor1;
    }
    return count1 * 512;
}

static uintarch_t ioctl(dev_t dev, uintarch_t fd, uint32_t type, uintarch_t a, uintarch_t b, uintarch_t c, uintarch_t d) {
    if (type == IO_CURSET) {
	cursor1 = a / 512;
	return 0;
    }
    return 1;
}


mod_t mod_ata_drive1 = {
    .load = init1,
    .read = read1,
    .ioctl = ioctl,
    .flags = MOD_FLAGS_DISK
};
