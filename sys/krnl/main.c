#include <fs/iso9660.h>
#include <fs/tarfs.h>
#include <krnl/elf.h>
#include <kernel.h>
#include <mod.h>
#if ARCH == ARCH_I386
#include <arch/x86/drivers/ide.h>
#include <arch/x86/drivers/vga_char.h>
#include <arch/x86/cpu/paging.h>
#include <krnl/syscalls.h>
#include <arch/x86/x86.h>
#endif

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
    devs[0].id = 0;
    devs[1].id = 1;
    mod_vga_char.load(&devs[0]);
    mod_ata_drive1.load(&devs[1]);
    mods[0] = &mod_vga_char;
    mods[1] = &mod_ata_drive1;
    #endif
    syscalls_init();
    int t = 0;

    byte_t elf[1024*16];
    iso9660fs.read(&devs[1], mods[1], 0, "init.", elf, 1024*16);

    kputsa((char*)elf);

    elf32_loader(elf);

    kputsa("HALTING");
    for(;;);
}
