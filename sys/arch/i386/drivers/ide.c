#include "kernel.h"
#include "mod.h"
#include <arch/x86/drivers/ide.h>

static uintarch_t cursor1 = 0;
static uintarch_t cursor1_offset = 0;

static void init1() {}
static uintarch_t read1(dev_t *dev, FS_RW_ARGS) {
    if (count == 0) return 0;

    uint8_t *buf8 = (uint8_t *)buf;
    uintarch_t total_read = 0;

    while (count > 0) {
        uint32_t lba = cursor1;
        outb(0x01F6, 0xE0 | ((lba >> 24) & 15));
        outb(0x01F2, 1);
        outb(0x01F3, lba & 0xFF);
        outb(0x01F4, (lba >> 8) & 0xFF);
        outb(0x01F5, (lba >> 16) & 0xFF);
        outb(0x01F7, 0x20);

        uint32_t timeout = 1000000;
        while (inb(0x01F7) & 0x80 && --timeout);
        if (!timeout || (inb(0x01F7) & 1)) break;

        timeout = 1000000;
        while (!(inb(0x01F7) & 0x08)) {
            if (inb(0x01F7) & 1 || !--timeout) break;
        }
        if (!timeout) break;

        uint8_t sector[512];
        for (uint32_t i = 0; i < 256; ++i) {
            uint16_t word = inw(0x01F0);
            sector[i * 2] = word & 0xFF;
            sector[i * 2 + 1] = word >> 8;
        }

        uint32_t offset = cursor1_offset;
        uint32_t available = 512 - offset;
        uint32_t to_copy = (count < available) ? count : available;

        kmemcpy(buf8, sector + offset, to_copy);

        buf8 += to_copy;
        count -= to_copy;
        total_read += to_copy;

        cursor1_offset += to_copy;
        if (cursor1_offset >= 512) {
            cursor1_offset = 0;
            ++cursor1;
        }
    }

    return total_read;
}

static uintarch_t ioctl(dev_t *dev, uintarch_t fd, uint32_t type, uintarch_t a, uintarch_t b, uintarch_t c, uintarch_t d) {
    if (type == IO_CURSET) {
        cursor1 = a / 512;
        cursor1_offset = a % 512;
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
