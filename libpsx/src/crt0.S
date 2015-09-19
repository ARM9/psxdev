
    .section .boot,"ax",@progbits
    .align 2
    .global _start
    .type _start, @function
_start:
    .set noat; .set noreorder

    la $sp, __sp
    la $gp, _gp

    li $t0, 1<<30   // Enable COP2, COP0 in kernel mode
    mtc0 $t0,$12    // Status register

    jal main
     mtc0 $0,$13    // Clear irq pending bits 8-9

0:  j 0b
     nop

// vim:ft=mips
