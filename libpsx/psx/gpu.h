
#ifndef LIBPSX_PSX_GPU_H
#define LIBPSX_PSX_GPU_H

#include <stdint.h>

// 15bpp format: bbbbb---ggggg---rrrrr---
// 24bpp format: bbbbbbbbggggggggrrrrrrrr

// GPU Registers
#define GP  ((volatile unsigned*)0x1F801810)

#ifdef GP0
#   undef GP0
#endif
#ifdef GP1
#   undef GP1
#endif
// Send command c with parameters p
#define GP0(c,p)  GP[0] = (((c)<<24)|(p))
#define GP1(c,p)  GP[1] = (((c)<<24)|(p))

#define DMODE_HRES_256  0x00
#define DMODE_HRES_320  0x01
#define DMODE_HRES_512  0x02
#define DMODE_HRES_640  0x03
#define DMODE_VRES_240  0x00
#define DMODE_VRES_480  0x04

void setDisplayMode(unsigned mode);

void setDisplayOrigin(uint16_t x, uint16_t y);

#endif

