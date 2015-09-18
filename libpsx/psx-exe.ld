
OUTPUT_FORMAT("elf32-littlemips")
OUTPUT_ARCH(mips)

EXTERN(_start)
ENTRY(_start)

MEMORY {
    wram    : ORIGIN = 0x80010000, LENGTH = 2M - 0x10000
    dcache  : ORIGIN = 0x1F800000, LENGTH = 0x400
}

__wram_top  = ORIGIN(wram) + LENGTH(wram);
__sp        = __wram_top - 0x100;

__dcache        = ORIGIN(dcache);
__dcache_top    = ORIGIN(dcache) + LENGTH(dcache);

SECTIONS {
    . = ORIGIN(wram);
    __text_start = .;
    .text : {
        *(.boot)
        . = ALIGN(4);
        *(.init)
        *(.text.unlikely .text.*_unlikely .text.unlikely.*)
        *(.text.exit .text.exit.*)
        *(.text.startup .text.startup.*)
        *(.text.hot .text.hot.*)
        *(.text .stub .text.* .gnu.linkonce.t.*)
        . = ALIGN(4);
    } > wram

    .fini : {
        KEEP (*(SORT_NONE(.fini)))
    } > wram
    . = ALIGN(4);
    __text_end = .;

    .rodata : {
        *(.rodata .rodata.* .rdata .rdata.* .gnu.linkonce.r.*)
    } > wram

    .rodata1 : {
        *(.rodata1)
    } > wram

    .sdata2 : {
        *(.sdata2 .sdata2.* .gnu.linkonce.s2.*)
    } > wram

    __sbss2_start = .;
    .sbss2 : {
        *(.sbss2 .sbss2.* .gnu.linkonce.sb2.*)
    } > wram
    __sbss2_end = .;

    .jcr : {
        KEEP (*(.jcr))
    } > wram

    .data.rel.ro : {
        *(.data.rel.ro.local* .gnu.linkonce.d.rel.ro.local.*) *(.data.rel.ro .data.rel.ro.* .gnu.linkonce.d.rel.ro.*)
    } > wram

    __data_start = .;
    .data : {
        *(.data .data.* .gnu.linkonce.d.*)
    } > wram

    .data1 : {
        *(.data1)
    } > wram

    .got.plt : {
        *(.got.plt)
    } > wram

    HIDDEN (_gp = ALIGN(16) + 0x7FF0);

    .got : {
        *(.got)
    } > wram

    .sdata : {
        *(.sdata .sdata.* .gnu.linkonce.s.*)
    } > wram
    . = ALIGN(4);
    __data_end = .;

    __bss_start = .;
    .sbss : {
        *(.dynsbss)
        *(.sbss .sbss.* .gnu.linkonce.sb.*)
        *(.scommon)
    } > wram

    .bss : {
        *(.dynbss)
        *(.bss .bss.* .gnu.linkonce.b.*)
        *(COMMON)
    } > wram
    . = ALIGN(4);
    __bss_end = .;

    __end = .;

    /DISCARD/ : { *(.MIPS.abiflags) }

    /* Everything is statically linked, so discard PLTs. */
    /DISCARD/ : { *(.rel.iplt) *(.rela.iplt) *(.rel.plt) *(.rela.plt) *(.plt) *(.iplt) }

    /* We don't make use of debugging information, so drop that, too. */
    /DISCARD/ : { *(.debug) *(.debug_srcinfo) *(.debug_sfnames) *(.debug_aranges) *(.debug_pubnames) *(.debug_info .gnu.linkonce.wi.*) *(.debug_abbrev) *(.debug_line .debug_line.* .debug_line_end ) *(.debug_frame) *(.debug_str) *(.debug_loc) *(.debug_macinfo) *(.debug_weaknames) *(.debug_funcnames) *(.debug_typenames) *(.debug_varnames) *(.debug_pubtypes) *(.debug_ranges) *(.debug_macro) *(.mdebug.abi32) *(.mdebug.abiN32) *(.mdebug.abi64) *(.mdebug.abiO64) *(.mdebug.eabi32) *(.mdebug.eabi64) }

    /* Discard things that the standard link script drops, too. */
    /DISCARD/ : { *(.note.GNU-stack) *(.gnu_debuglink) *(.gnu.lto_*) }
}
