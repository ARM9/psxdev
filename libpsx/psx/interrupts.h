
#ifndef LIBPSX_PSX_INTERRUPTS_H
#define LIBPSX_PSX_INTERRUPTS_H

#define IrqVblank   0x001
#define IrqGpu      0x002
#define IrqCdrom    0x004
#define IrqDma      0x008
#define IrqTimer0   0x010
#define IrqTimer1   0x020
#define IrqTimer2   0x040
#define IrqMemcard  0x080
#define IrqSio      0x100
#define IrqSpu      0x200
#define IrqPio      0x400

void waitVblank(void);

#endif
