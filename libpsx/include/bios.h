
#ifndef LIBPSX_BIOS_H
#define LIBPSX_BIOS_H

#define BIOS_CALL(x) __asm__ __volatile__ (\
        "ori $t1, $0, " #x "\n\t"\
        "j 0x800000A0\n\t":::"t1");

#endif

