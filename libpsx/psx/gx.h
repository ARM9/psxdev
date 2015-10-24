#pragma once

#include <stdint.h>

#define GX_BIT(n)         (1 << (n))
#define GX_BGR(b, g, r)   (((r) << 16) | ((g) << 8) | (b))
#define GX_RGB(r, g, b)   (((b) << 16) | ((g) << 8) | (r))
#define GX_XY20(x, y)     (((y) << 10) | (x))
#define GX_XY32(x, y)     (((y) << 16) | (x))

/* Initializes the GPU and the library */
void GX_Init(void);

/* Set area to clip geometry to (optional) */
void GX_SetScissorRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

/* Syncs to V-blank */
void GX_Sync(void);

/* Fills a rectangle in window space with an RGB color */
void GX_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color);

