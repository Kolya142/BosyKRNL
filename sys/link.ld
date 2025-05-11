ENTRY(_start)
SECTIONS {
    . = 0x100000;
    .mb : { KEEP(*(.mb)) }
    .text : ALIGN(4) { *(.text) }
    .data : ALIGN(4) { *(.data) }
    .bss  : ALIGN(4) {
        *(COMMON)
        *(.bss)
    }    
}
