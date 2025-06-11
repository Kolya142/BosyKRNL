ENTRY(_start)

SECTIONS {
    . = 0x100000;

    .text : {
        KEEP(*(.init))
        *(.text*)
        *(.rodata*)
    }

    .data : {
        *(.data*)
    }

    .bss : {
        *(.bss*)
        *(COMMON)
    }

    _end = .;
}
