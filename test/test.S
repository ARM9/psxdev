
    .text
    .align 2
    .global sectionTest
sectionTest:
    .set noat; .set noreorder
    la $1, car
    la $2, baz
    lw $3,0($1)
    lw $4,0($2)
    j sectionTest
     nop

    .data
    .align 2
foo:
    .byte 0xfeedbacc
    .byte 0xfeedbacc>>8
    .word   0xfeedbacc
    .int    0xabad1dea
    
    .rdata
    .align 2
bar:
    .hword 0xfeed
    .hword 0xbacc
    .hword -1

    .bss
    .align 2
car:
    .word -1
    .word 55

    .section .sbss,"aw",@nobits
    .align 3
baz:
    .dword 0xfeedbacccafe

// vim:ft=mips
