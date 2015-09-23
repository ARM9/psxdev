#include <psx/io.h>
#include <psx/interrupts.h>

void waitVblank(void) {
    while(!(IRQ_STAT & IrqVblank));
    IRQ_STAT = ~IrqVblank;
    unsigned cop0_sr_flag = 1<<8;
    __asm__ __volatile__ (
            "mtc0 %[t], $12\n\t"
            ::[t] "r" (cop0_sr_flag)
            :);
}

