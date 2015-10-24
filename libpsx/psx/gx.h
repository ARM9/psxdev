#pragma once

#include <stdint.h>

/* Utility macros for both private and public use */
#define GX_BIT(n)            	(1 << (n))
#define GX_BGR(b, g, r)      	(((r) << 16) | ((g) << 8) | (b))
#define GX_RGB(r, g, b)      	(((b) << 16) | ((g) << 8) | (r))
#define GX_XY20(x, y)        	(((y) << 10) | (x))
#define GX_XY32(x, y)        	(((y) << 16) | (x))
#define GX_F16(integer, frac)	(((frac) << 8)  | (integer))
#define GX_F32(integer, frac)	(((frac) << 16) | (integer))
#define GX_PACK_VEC2(v) 		GX_XY32(v.x, v.y)

/* Typedefs to serve for easy understanding of parameters */
typedef uint32_t gx_xy32; // 32-bit x y coordinate (each component is 16 bits)
typedef uint32_t gx_xy20; // 20-bit x y coordinate (each component is 10 bits)
typedef uint16_t gx_f16; // 16-bit fixed-point decimal
typedef uint32_t gx_f32; // 32-bit fixed-point decimal
typedef uint32_t gx_rgb24; // 24-bit RGB color
typedef uint32_t gx_bgr24; // 24-bit BGR color

/* Represents a fixed-point 2D vector */
typedef struct
{
	gx_f16 x;
	gx_f16 y;
}
gx_vec2_t;

/* Represents a fixed-point 3D vector */
typedef struct
{
	gx_f16 x;
	gx_f16 y;
	gx_f16 z;
}
gx_vec3_t;

/* Initializes the GPU and the library */
void GX_Init(void);

/* Syncs to V-blank */
void GX_Sync(void);

/* Sets area to clip geometry to (optional) */
void GX_SetScissorRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

/* Fills a rectangle in window space with a color */
void GX_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, gx_rgb24 color);

/* Draws a monotone triangle */
void GX_DrawTriangle_SingleColor(
	gx_vec2_t v0,
	gx_vec2_t v1,
	gx_vec2_t v2,
	gx_rgb24 color
	);

/* Draws a monotone quad
	Vertex order:
	v0--------------v2
	|                |
	|                |
	|                |
	|                |
	|                |
	|                |
	v1--------------v3
	
 */
void GX_DrawQuad_SingleColor(
	gx_vec2_t v0,
	gx_vec2_t v1,
	gx_vec2_t v2,
	gx_vec2_t v3,
	gx_rgb24 color
	);

	