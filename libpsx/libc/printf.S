
    .text
    .align 2
    .global printf
    .type printf, @function
printf:
    .set noat; .set noreorder
    // if the assembler/linker complains, use this:
    //ori $t0, $0, 0x00A0
    //jr $t0
    //ori $t1, $0, 0x3F

    j 0x000000A0
    ori $t1, $0, 0x3F

    .size printf, .-printf

// vim:ft=mips
