#include <kernel.h>
#include <mod.h>
#if ARCH == ARCH_I386
#include <arch/x86/drivers/vga_char.h>
#endif

static mod_t *mods[512] = {0};

void _start() {
    #if ARCH == ARCH_I386
    asm("mov $0x200000, %esp");
    mod_vga_char.load(0);
    mods[0] = &mod_vga_char;
    #endif
    int t = 0;
    
    for(;;) {
        for (uintarch_t i = 0; i < 512; ++i) {
	    if (mods[i] && mods[i]->flags & MOD_FLAGS_CHAROUT && mods[i]->ioctl && mods[i]->write) {
		mods[i]->ioctl(i, 1, IO_CURSET, (t >> 1) % (80 * 25), 0, 0, 0);
		mods[i]->write(i, 1, (char[]) {t % 256}, 1);
	    }
	}
	++t;
    }
}
