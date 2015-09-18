
    .text
    .align 2
    .global printf
    .type printf, @function
printf:
    .set noat; .set noreorder
    j 0x800000A0
    ori $t1, $0, 0x3F

    .size printf, .-printf

// vim:ft=mips
