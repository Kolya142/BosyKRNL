#include <fs/tarfs.h>
#include <krnl/elf.h>
#include <kernel.h>
#include <mod.h>
#if ARCH == ARCH_I386
#include <arch/x86/drivers/ide.h>
#include <arch/x86/drivers/vga_char.h>
#include <arch/x86/x86.h>
#endif

static mod_t *mods[512] = {0};

void _start() {
    cpu_init();
    #if ARCH == ARCH_I386
    asm("mov $0x200000, %esp");
    mod_vga_char.load(0);
    mod_ata_drive1.load(1);
    mods[0] = &mod_vga_char;
    mods[1] = &mod_ata_drive1;
    #endif
    int t = 0;

    // tarfs_header_t *my_elf = tarfs_find_file("init", tar);
    
    for(;;) {
	mods[0]->ioctl(0, 1, IO_CURSET, 0, 0, 0, 0);
	char buf[1024];
	mods[1]->ioctl(1, 0, IO_CURSET, 1024*16, 0, 0, 0);
	mods[1]->read(1, 0, buf, 1024);
	mods[0]->write(0, 1, buf, 1024);
	++t;
	// elf32_loader((void*)my_elf + 512);
    }
}
