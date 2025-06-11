#include <arch/intf/userland.h>
 #include <krnl/memory.h>
 #include <krnl/shred.h>
 #include <krnl/elf.h>
 #include <mod.h>
 
 static uintarch_t get_stack(task_t *task) {
     #define STACK_SIZE (16)
     for (uintarch_t i = - 4096; i >= - (STACK_SIZE * 4096); i -= 4096) {
         uintarch_t page = paging.alloc_page();
         paging.map_page(page, i, paging.get_hardware_flags(MEMDEV_READ|MEMDEV_USER|MEMDEV_WRITE|MEMDEV_PRESENT));
 	page_t ppage;
 	ppage.virt = i;
 	ppage.real = page;
 	vector_push_back(&task->pages, &ppage);
     }
     return - 4096;
 }
 
 int elf32_loader(uint8_t *prog) {
     elf32head_t *elf = (elf32head_t *)prog;
     if (elf->e_magic != 0x464C457F) {
         return -1;
     }
     if (elf->e_arch != 1 || elf->e_machine != 3) {
         return 2;
     }
     task_t *task = task_create((void *)elf->e_entry, (void *)-4096, 0x23, 0x1B, FALSE);
     get_stack(task);
     elf32prog_t *ph = (elf32prog_t*)(prog + elf->e_phoff);
     for (uint32_t i = 0; i < elf->e_phnum; ++i, ++ph) {
         if (ph->e_type != 1) continue;
         
         for (uint32_t off = 0; off < ph->e_memsz; off += 0x1000) {
             void *poff = (void*)ph->e_vaddr + off;
             uintarch_t page = paging.alloc_page();
             paging.map_page(page, (uintarch_t)poff, paging.get_hardware_flags(MEMDEV_READ|MEMDEV_USER|MEMDEV_WRITE|MEMDEV_PRESENT));
 	    
 	    page_t ppage;
 	    ppage.virt = (uintarch_t)poff;
 	    ppage.real = page;
 	    vector_push_back(&task->pages, &ppage);
 
             if (off < ph->e_filesz) {
                 uint32_t len = 0x1000;
                 if (ph->e_filesz - off < len) len = ph->e_filesz - off;
                 kmemcpy(poff, prog + ph->e_offset + off, len);
 
                 if (len < 0x1000 && ph->e_memsz > ph->e_filesz) {
                     kmemset(poff + len, 0, 0x1000 - len);
                 }
             }
             else {
                 kmemset(poff, 0, 0x1000);
             }
         }
     }
     SWITCH_TO_USERLAND(elf->e_entry, -4096);
     return 0;
 }
 
