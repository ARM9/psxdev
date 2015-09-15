
OUTPUT_FORMAT("elf32-bigmips")
OUTPUT_ARCH(mips)

EXTERN(_start)
ENTRY(_start)

MEMORY {
    wram : ORIGIN = 0x80010000, LENGTH = 2M - 0x10000
}

__wram_top   = ORIGIN(wram) + LENGTH(wram);
__sp        = __wram_top - 0x100;

SECTIONS {
    . = ORIGIN(wram);
    .text (ALIGN(4)) : {
        __text_start = .;
        *(.init)
        *(.text)
        *(.text.*)
        . = ALIGN(4);
        __text_end = .;
    } > wram

    .rodata : {
        *(.rodata .rodata.* .rdata .rdata.*)
        . = ALIGN(4);
    } > wram

    __data_start = .;
    .data : {
        *(.data)
        *(.data.*)
        . = ALIGN(4);
    } > wram

    HIDDEN (_gp = ALIGN(16) + 0x7FF0);

    .sdata : {
        *(.sdata)
        *(.sdata.*)
    } > wram
    __data_end = .;

    __bss_start = .;
    .sbss : {
        *(.sbss)
        *(.sbss.*)
        *(.scommon)
    } > wram
    .bss : {
        *(.bss)
        *(.bss.*)
        *(COMMON)
    } > wram
    . = ALIGN(4);
    __bss_end = .;

    __end = .;

    /DISCARD/ : { *(.MIPS.abiflags) }
}
