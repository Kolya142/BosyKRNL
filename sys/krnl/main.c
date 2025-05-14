#include <fs/iso9660.h>
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

void main();

__attribute__((naked))
void _start() {
    #if ARCH == ARCH_I386
    asm("mov $0x200000, %esp");
    #endif
    asm("call main");
}

void main() {
    #if ARCH == ARCH_I386
    cpu_init();
    mod_vga_char.load(0);
    mod_ata_drive1.load(1);
    mods[0] = &mod_vga_char;
    mods[1] = &mod_ata_drive1;
    #endif
    int t = 0;

    char tar[8192];
    dev_t d = 1;
    iso9660_dir_entry_t *de = iso9660_get(mods[1], &d, "distro.tar");
    mods[1]->ioctl(1, 0, IO_CURSET, de->extent_lba_le * 2048, 0, 0, 0);
    mods[1]->read(1, 0, tar, de->data_length_le * 2048);
    tarfs_header_t *my_elf = tarfs_find_file("init", tar);
    if (!my_elf) return;
    
    for(;;) {
	mods[0]->ioctl(0, 1, IO_CURSET, 0, 0, 0, 0);
	mods[0]->write(0, 1, (void *)0x100000 + t, 1024);
	++t;
	elf32_loader((void *)my_elf + 512);
    }
}
