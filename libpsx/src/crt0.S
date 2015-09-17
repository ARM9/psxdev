
    .section .boot,"ax",@progbits
    .align 2
    .global _start
    .type _start,@function
_start:
    .set noat; .set noreorder

    la $sp, __sp
    la $gp, _gp

    jal main
     mtc0 $0,$13     // COP0_13

0:  j 0b
     nop

// vim:ft=mips
