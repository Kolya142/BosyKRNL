#include <krnl/shred.h>
#include <fs/iso9660.h>
#include <fs/tarfs.h>
#include <krnl/elf.h>
#include <kernel.h>
#include <mod.h>
#if ARCH == ARCH_RISCV64
#include <arch/riscv64/drivers/uart.h>
#include <arch/riscv64/riscv64.h>
#endif
#if ARCH == ARCH_I386
#include <arch/x86/drivers/keyboard.h>
#include <arch/x86/drivers/vga_char.h>
#include <arch/x86/drivers/ide.h>
#include <arch/x86/cpu/paging.h>
#include <krnl/syscalls.h>
#include <arch/x86/x86.h>
#endif

void main();

__attribute__((naked))
__attribute__((section(".init")))
void _start() {
#if ARCH == ARCH_I386
    asm("mov $0x200000, %esp");
    asm("call main");
#endif
#if ARCH == ARCH_X86_64
    asm("mov $0x200000, %rsp");
    asm("push %rbx");
    asm("call main");
#endif
/*
/*
#if ARCH == ARCH_RISCV64
    asm("li sp, 0x80200000");
#endif
*/
#if ARCH == ARCH_MIPS64EL
    asm(
	"lui $sp, 0xcfc0\n"
	"jal main"
    );
#endif
}

struct multiboot {
	uint32_t total;
	uint32_t reservd;
} __attribute__((packed));

struct multiboot_tag {
	uint32_t type;
	uint32_t size;
} __attribute__((packed));

void main(struct MultiBoot *mb) {
#if ARCH == ARCH_I386
    cpu_init();
    devs[0].id = 0;
    devs[1].id = 1;
    mod_vga_char.load(&devs[0]);
    mod_ata_drive1.load(&devs[1]);
    mods[0] = &mod_vga_char;
    mods[1] = &mod_ata_drive1;
    keyboard_init();
#endif
#if ARCH == ARCH_X86_64
    {
        void *ptr = (void *)((uint64_t)mb)+8;
        for (;;) {
            struct multiboot_tag *tag = ptr;
            if (tag->type == 0) {
                break;
            }
            if (tag->type == 8) {
                struct {
                    uint32_t type;
                    uint32_t size;
                    uint64_t addr;
                    uint32_t pitch;
                    uint32_t width;
                    uint32_t height;
                    uint8_t bpp;
                    uint8_t fb_type;
                    uint16_t reserved;
                } __attribute__((packed)) *fb = (void *)tag;
                volatile uint32_t *vvram = (uint32_t*)fb->addr;
                for (int i = 0; i < 6400; ++i) vvram[i] = 0xFF00FF;
            }
            ptr += (tag->size + 7) & ~7;
        }
    }
#endif
#if ARCH == ARCH_RISCV64
    cpu_init();

    devs[0].id = 0;
    mods[0] = &mod_uart;
#endif
#if ARCH == ARCH_MIPS64EL
    void cpu_init();
    void uart_putc(char c);
    cpu_init();
    uart_putc('h');
#endif
    
    kheap_init();
    task_init();
    syscalls_init();
    int t = 0;

    struct stat elf_stat;
    if (!iso9660fs.stat(&devs[1], mods[1], "init", &elf_stat)) {
	kputsa("\n\nkpanic: INIT not found at iso9660:/init");
	for(;;);
    }
    byte_t *elf = kmalloc(elf_stat.size);
    iso9660fs.read(&devs[1], mods[1], 0, "init", elf, 1024*16);

    elf32_loader(elf);

    kfree(elf);
    
    kputsa("\nHALTING");
    for(;;);
}
