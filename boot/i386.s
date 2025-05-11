[bits 16]
pps:
    cli
    lgdt [gdt_descriptor]
    mov eax, cr0
    or eax, 1
    mov cr0, eax
    jmp 8:pp

[bits 32]
pp:
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov ss, ax
    mov fs, ax
    mov gs, ax
    jmp 8:pp2

pp2:
    mov esp, 0x200000
    call 0x100000+2048
    hlt
    jmp $

gdt_start:
   ;    012345678abcdefg
   dq 0x0000000000000000
   dq 0x00CF9A000000FFFF
   dq 0x00CF92000000FFFF
   dq 0x00AF9A000000FFFF
   dq 0x00AF92000000FFFF
gdt_end:

gdt_descriptor:
   dw gdt_end - gdt_start - 1
   dq gdt_start



times 2048-($-$$) db 0
