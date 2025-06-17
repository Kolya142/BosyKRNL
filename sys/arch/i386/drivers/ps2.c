#include <bosykrnl/arch/x86/x86.h>
#include <bosykrnl/arch/x86/drivers/ps2.h>
#include <bosykrnl/arch/x86/cpu/pit.h>

static void ps2_flush() {
    while (inb(0x64) & 1) inb(0x60);
}

static int ps2_test() { return inb(0x60) != 0xFC; }

static void ps2_wait(int how) {
    uint32_t timeout = 1000000;
    if (!how) {
	while (--timeout) {
	    if ((inb(0x64) & 1) == 1) {
		return;
	    }
	}
	return;
    }
    else {
	while (--timeout) {
	    if ((inb(0x64) & 2) == 0) {
		return;
	    }
	}
	return;
    }
}

static uintarch_t ps2_read() {
    ps2_wait(0);
    uint8_t byte = inb(0x60);
    return byte;
}

static void ps2_write(uintarch_t cmd, uintarch_t byte) {
    ps2_wait(1);
    outb(0x64, cmd);
    ps2_wait(1);
    outb(0x60, byte);
}

static void ps2_load() {
    outb(0x64, 0xAD);
    outb(0x64, 0xA7);

    ps2_flush();

    ps2_wait(1);
    outb(0x64, 0xAA);
    ps2_wait(0);

    ps2_test();

    outb(0x64, 0x20);
    uint8_t status = inb(0x60);
    outb(0x64, 0x60);
    outb(0x60, status | 0b11);

    outb(0x64, 0xAE);
    if (status & 0x20) outb(0x64, 0xAB);
}
static uintarch_t ps2_ioctl(dev_t *dev, uintarch_t fd, uint32_t type, uintarch_t a, uintarch_t b, uintarch_t c, uintarch_t d) {
    switch (type) {
    case CTIO_RESET: {
	ps2_load();
	return 0;
    }
    case CTIO_FLUSH: {
	ps2_flush();
	return 0;
    }
    case CTIO_READ: {
	return ps2_read();
	return 0;
    }
    case CTIO_WRITE: {
        ps2_write(a, b);
	return 0;
    }
    case CTIO_CHECK: {
	return ps2_test();
    }
    }
    return -1;
}

mod_t ps2 = {
    .load = ps2_load,
    .ioctl = ps2_ioctl,
    .flags = MOD_FLAGS_CONTROLLER
};
