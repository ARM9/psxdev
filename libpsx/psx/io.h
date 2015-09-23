
#ifndef LIBPSX_PSX_IO_H
#define LIBPSX_PSX_IO_H

#ifndef __LANGUAGE_ASSEMBLY
#   define IO_8(x) (*(volatile unsigned char *)x)
#   define IO_16(x) (*(volatile unsigned short *)x)
#   define IO_32(x) (*(volatile unsigned int *)x)
#   define IO_S8(x) (*(volatile char *)x)
#   define IO_S16(x) (*(volatile short *)x)
#   define IO_S32(x) (*(volatile int *)x)
#else
#   define IO_8(x) (x)
#   define IO_16(x) (x)
#   define IO_32(x) (x)
#   define IO_S8(x) (x)
#   define IO_S16(x) (x)
#   define IO_S32(x) (x)
#endif

#define IO_BASE         0x1F801000  // Various io
#define IO_BASE_EXP2    0x1F802000  // Expansion region 2

// Memory Control 1
// probably don't need to touch these
// 0x1F801000 4    Expansion 1 Base Address (usually 1F000000h)
// 0x1F801004 4    Expansion 2 Base Address (usually 1F802000h)
// 0x1F801008 4    Expansion 1 Delay/Size (usually 0013243Fh; 512Kbytes 8bit-bus)
// 0x1F80100C 4    Expansion 3 Delay/Size (usually 00003022h; 1 byte)
// 0x1F801010 4    BIOS ROM    Delay/Size (usually 0013243Fh; 512Kbytes 8bit-bus)
// 0x1F801014 4    SPU_DELAY   Delay/Size (usually 200931E1h)
// 0x1F801018 4    CDROM_DELAY Delay/Size (usually 00020843h or 00020943h)
// 0x1F80101C 4    Expansion 2 Delay/Size (usually 00070777h; 128-bytes 8bit-bus)
// 0x1F801020 4    COM_DELAY / COMMON_DELAY (00031125h or 0000132Ch or 00001325h)

// Peripheral I/O Ports
#define JOY_DATA    IO_32(0x1F801040) // 1/4  Joypad/Memory Card Data (R/W)
#define JOY_STAT    IO_32(0x1F801044) // 4    Joypad/Memory Card Status (R)
#define JOY_MODE    IO_16(0x1F801048) // 2    Joypad/Memory Card Mode (R/W)
#define JOY_CTRL    IO_16(0x1F80104A) // 2    Joypad/Memory Card Control (R/W)
#define JOY_BAUD    IO_16(0x1F80104E) // 2    Joypad/Memory Card Baudrate (R/W)
#define SIO_DATA    IO_32(0x1F801050) // 1/4  Serial Port Data (R/W)
#define SIO_STAT    IO_32(0x1F801054) // 4    Serial Port Status (R)
#define SIO_MODE    IO_16(0x1F801058) // 2    Serial Port Mode (R/W)
#define SIO_CTRL    IO_16(0x1F80105A) // 2    Serial Port Control (R/W)
#define SIO_MISC    IO_16(0x1F80105C) // 2    Serial Port Internal Register (R/W)
#define SIO_BAUD    IO_16(0x1F80105E) // 2    Serial Port Baudrate (R/W)
// Memory Control 2
#define RAM_SIZE    IO_32(0x1F801060) // 4/2  (usually 00000B88h; 2MB RAM mirrored in first 8MB)
// Interrupt Control
#define IRQ_STAT    IO_16(0x1F801070) // 2    Interrupt status register
#define IRQ_MASK    IO_16(0x1F801074) // 2    Interrupt mask register

/*
// DMA Registers
  0x1F80108x      DMA0 channel 0 - MDECin
  0x1F80109x      DMA1 channel 1 - MDECout
  0x1F8010Ax      DMA2 channel 2 - GPU (lists + image data)
  0x1F8010Bx      DMA3 channel 3 - CDROM
  0x1F8010Cx      DMA4 channel 4 - SPU
  0x1F8010Dx      DMA5 channel 5 - PIO (Expansion Port)
  0x1F8010Ex      DMA6 channel 6 - OTC (reverse clear OT) (GPU related)
  0x1F8010F0      DPCR - DMA Control register
  0x1F8010F4      DICR - DMA Interrupt register
  0x1F8010F8      unknown
  0x1F8010FC      unknown
// Timers (aka Root counters)
  0x1F80110x      Timer 0 Dotclock
  0x1F80111x      Timer 1 Horizontal Retrace
  0x1F80112x      Timer 2 1/8 system clock
// CDROM Registers (Address.Read/Write.Index)
  0x1F801800.x.x   1   CD Index/Status Register (Bit0-1 R/W, Bit2-7 Read Only)
  0x1F801801.R.x   1   CD Response Fifo (R) (usually with Index1)
  0x1F801802.R.x   1/2 CD Data Fifo - 8bit/16bit (R) (usually with Index0..1)
  0x1F801803.R.0   1   CD Interrupt Enable Register (R)
  0x1F801803.R.1   1   CD Interrupt Flag Register (R/W)
  0x1F801803.R.2   1   CD Interrupt Enable Register (R) (Mirror)
  0x1F801803.R.3   1   CD Interrupt Flag Register (R/W) (Mirror)
  0x1F801801.W.0   1   CD Command Register (W)
  0x1F801802.W.0   1   CD Parameter Fifo (W)
  0x1F801803.W.0   1   CD Request Register (W)
  0x1F801801.W.1   1   Unknown/unused
  0x1F801802.W.1   1   CD Interrupt Enable Register (W)
  0x1F801803.W.1   1   CD Interrupt Flag Register (R/W)
  0x1F801801.W.2   1   Unknown/unused
  0x1F801802.W.2   1   CD Audio Volume for Left-CD-Out to Left-SPU-Input (W)
  0x1F801803.W.2   1   CD Audio Volume for Left-CD-Out to Right-SPU-Input (W)
  0x1F801801.W.3   1   CD Audio Volume for Right-CD-Out to Right-SPU-Input (W)
  0x1F801802.W.3   1   CD Audio Volume for Right-CD-Out to Left-SPU-Input (W)
  0x1F801803.W.3   1   CD Audio Volume Apply Changes (by writing bit5=1)
*/
#define GP0   IO_32(0x1F801810)
    // Write 4   GP0 Send GP0 Commands/Packets (Rendering and VRAM Access)
    // Read  4   GPUREAD Read responses to GP0(C0h) and GP1(10h) commands
#define GP1   IO_32(0x1F801814)
    // Write 4   GP1 Send GP1 Commands (Display Control)
    // Read  4   GPUSTAT Read GPU Status Register

/*
MDEC Registers
  0x1F801820.Write 4   MDEC Command/Parameter Register (W)
  0x1F801820.Read  4   MDEC Data/Response Register (R)
  0x1F801824.Write 4   MDEC Control/Reset Register (W)
  0x1F801824.Read  4   MDEC Status Register (R)
SPU Voice 0..23 Registers
  0x1F801C00+N*10h 4   Voice 0..23 Volume Left/Right
  0x1F801C04+N*10h 2   Voice 0..23 ADPCM Sample Rate
  0x1F801C06+N*10h 2   Voice 0..23 ADPCM Start Address
  0x1F801C08+N*10h 4   Voice 0..23 ADSR Attack/Decay/Sustain/Release
  0x1F801C0C+N*10h 2   Voice 0..23 ADSR Current Volume
  0x1F801C0E+N*10h 2   Voice 0..23 ADPCM Repeat Address
SPU Control Registers
  0x1F801D80 4  Main Volume Left/Right
  0x1F801D84 4  Reverb Output Volume Left/Right
  0x1F801D88 4  Voice 0..23 Key ON (Start Attack/Decay/Sustain) (W)
  0x1F801D8C 4  Voice 0..23 Key OFF (Start Release) (W)
  0x1F801D90 4  Voice 0..23 Channel FM (pitch lfo) mode (R/W)
  0x1F801D94 4  Voice 0..23 Channel Noise mode (R/W)
  0x1F801D98 4  Voice 0..23 Channel Reverb mode (R/W)
  0x1F801D9C 4  Voice 0..23 Channel ON/OFF (status) (R)
  0x1F801DA0 2  Unknown? (R) or (W)
  0x1F801DA2 2  Sound RAM Reverb Work Area Start Address
  0x1F801DA4 2  Sound RAM IRQ Address
  0x1F801DA6 2  Sound RAM Data Transfer Address
  0x1F801DA8 2  Sound RAM Data Transfer Fifo
  0x1F801DAA 2  SPU Control Register (SPUCNT)
  0x1F801DAC 2  Sound RAM Data Transfer Control
  0x1F801DAE 2  SPU Status Register (SPUSTAT) (R)
  0x1F801DB0 4  CD Volume Left/Right
  0x1F801DB4 4  Extern Volume Left/Right
  0x1F801DB8 4  Current Main Volume Left/Right
  0x1F801DBC 4  Unknown? (R/W)
SPU Reverb Configuration Area
  0x1F801DC0 2  dAPF1  Reverb APF Offset 1
  0x1F801DC2 2  dAPF2  Reverb APF Offset 2
  0x1F801DC4 2  vIIR   Reverb Reflection Volume 1
  0x1F801DC6 2  vCOMB1 Reverb Comb Volume 1
  0x1F801DC8 2  vCOMB2 Reverb Comb Volume 2
  0x1F801DCA 2  vCOMB3 Reverb Comb Volume 3
  0x1F801DCC 2  vCOMB4 Reverb Comb Volume 4
  0x1F801DCE 2  vWALL  Reverb Reflection Volume 2
  0x1F801DD0 2  vAPF1  Reverb APF Volume 1
  0x1F801DD2 2  vAPF2  Reverb APF Volume 2
  0x1F801DD4 4  mSAME  Reverb Same Side Reflection Address 1 Left/Right
  0x1F801DD8 4  mCOMB1 Reverb Comb Address 1 Left/Right
  0x1F801DDC 4  mCOMB2 Reverb Comb Address 2 Left/Right
  0x1F801DE0 4  dSAME  Reverb Same Side Reflection Address 2 Left/Right
  0x1F801DE4 4  mDIFF  Reverb Different Side Reflection Address 1 Left/Right
  0x1F801DE8 4  mCOMB3 Reverb Comb Address 3 Left/Right
  0x1F801DEC 4  mCOMB4 Reverb Comb Address 4 Left/Right
  0x1F801DF0 4  dDIFF  Reverb Different Side Reflection Address 2 Left/Right
  0x1F801DF4 4  mAPF1  Reverb APF Address 1 Left/Right
  0x1F801DF8 4  mAPF2  Reverb APF Address 2 Left/Right
  0x1F801DFC 4  vIN    Reverb Input Volume Left/Right
SPU Internal Registers
  0x1F801E00+N*04h  4 Voice 0..23 Current Volume Left/Right
  0x1F801E60      20h Unknown? (R/W)
  0x1F801E80     180h Unknown? (Read: FFh-filled) (Unused or Write only?)
Expansion Region 2 (default 128 bytes, max 8 KBytes)
  0x1F802000      80h Expansion Region (8bit data bus, crashes on 16bit access?)
Expansion Region 2 - Dual Serial Port (for TTY Debug Terminal)
  0x1F802020/1st    DUART Mode Register 1.A (R/W)
  0x1F802020/2nd    DUART Mode Register 2.A (R/W)
  0x1F802021/Read   DUART Status Register A (R)
  0x1F802021/Write  DUART Clock Select Register A (W)
  0x1F802022/Read   DUART Toggle Baud Rate Generator Test Mode (Read=Strobe)
  0x1F802022/Write  DUART Command Register A (W)
  0x1F802023/Read   DUART Rx Holding Register A (FIFO) (R)
  0x1F802023/Write  DUART Tx Holding Register A (W)
  0x1F802024/Read   DUART Input Port Change Register (R)
  0x1F802024/Write  DUART Aux. Control Register (W)
  0x1F802025/Read   DUART Interrupt Status Register (R)
  0x1F802025/Write  DUART Interrupt Mask Register (W)
  0x1F802026/Read   DUART Counter/Timer Current Value, Upper/Bit15-8 (R)
  0x1F802026/Write  DUART Counter/Timer Reload Value,  Upper/Bit15-8 (W)
  0x1F802027/Read   DUART Counter/Timer Current Value, Lower/Bit7-0 (R)
  0x1F802027/Write  DUART Counter/Timer Reload Value,  Lower/Bit7-0 (W)
  0x1F802028/1st    DUART Mode Register 1.B (R/W)
  0x1F802028/2nd    DUART Mode Register 2.B (R/W)
  0x1F802029/Read   DUART Status Register B (R)
  0x1F802029/Write  DUART Clock Select Register B (W)
  0x1F80202A/Read   DUART Toggle 1X/16X Test Mode (Read=Strobe)
  0x1F80202A/Write  DUART Command Register B (W)
  0x1F80202B/Read   DUART Rx Holding Register B (FIFO) (R)
  0x1F80202B/Write  DUART Tx Holding Register B (W)
  0x1F80202C/None   DUART Reserved Register (neither R nor W)
  0x1F80202D/Read   DUART Input Port (R)
  0x1F80202D/Write  DUART Output Port Configuration Register (W)
  0x1F80202E/Read   DUART Start Counter Command (Read=Strobe)
  0x1F80202E/Write  DUART Set Output Port Bits Command (Set means Out=LOW)
  0x1F80202F/Read   DUART Stop Counter Command (Read=Strobe)
  0x1F80202F/Write  DUART Reset Output Port Bits Command (Reset means Out=HIGH)
Expansion Region 2 - Int/Dip/Post
  0x1F802000 1 DTL-H2000: ATCONS STAT (R)
  0x1F802002 1 DTL-H2000: ATCONS DATA (R and W)
  0x1F802004 2 DTL-H2000: Whatever 16bit data ?
  0x1F802030 1/4 DTL-H2000: Secondary IRQ10 Flags
  0x1F802032 1 DTL-H2000: Whatever IRQ Control ?
  0x1F802040 1 DTL-H2000: Bootmode "Dip switches" (R)
  0x1F802041 1 PSX: POST (external 7 segment display, indicate BIOS boot status)
  0x1F802042 1 DTL-H2000: POST/LED (similar to POST) (other addr, 2-digit wide) 
  0x1F802070 1 PS2: POST2 (similar to POST, but PS2 BIOS uses this address)
Expansion Region 2 - Nocash Emulation Expansion
  0x1F802060 Emu-Expansion ID1 "E" (R)
  0x1F802061 Emu-Expansion ID2 "X" (R)
  0x1F802062 Emu-Expansion ID3 "P" (R)
  0x1F802063 Emu-Expansion Version (01h) (R)
  0x1F802064 Emu-Expansion Enable1 "O" (R/W)
  0x1F802065 Emu-Expansion Enable2 "N" (R/W)
  0x1F802066 Emu-Expansion Halt (R)
  0x1F802067 Emu-Expansion Turbo Mode Flags (R/W)

Expansion Region 3 (default 1 byte, max 2 MBytes)
  0x1FA00000 - Not used by BIOS or any PSX games
  0x1FA00000 - POST3 (similar to POST, but PS2 BIOS uses this address)
BIOS Region (default 512 Kbytes, max 4 MBytes)
  0x1FC00000 0x80000   BIOS ROM (512Kbytes) (Reset Entrypoint at BFC00000h)

Coprocessor Registers
  COP0 System Control Coprocessor           - 32 registers (not all used)
  COP1 N/A
  COP2 Geometry Transformation Engine (GTE) - 64 registers (most are used)
  COP3 N/A
*/

// Memory Control 3 (Cache Control)
#define CACHE_CTRL  0xFFFE0130  // Cache control io

#endif

