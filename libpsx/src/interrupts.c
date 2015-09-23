#include <psx/io.h>
#include <psx/interrupts.h>

void waitVblank(void) {
    while(!(IRQ_STAT & IRQ_VBLANK));
    IRQ_STAT = ~IRQ_VBLANK;
    int dummy;
    __asm__ __volatile__ (
            "li %[t], 1<<8\n\t"
            "mtc0 %[t], $12\n\t"
            :[t] "=r" (dummy)
            ::);
}

