/****************************************************************************
                          PSX GPU Graphics Wrapper
 ***************************************************************************/
 
#ifndef LIBPSX_GX_H
#define LIBPSX_GX_H

#include <psx/gpu.h>


/* Utility macros for both private and public use */
#define GX_BIT(n)            	 (1 << (n))
#define GX_BITS(n)               ((1 << (n)) - 1)
#define GX_BGR(b, g, r)      	 (((r) << 16) | ((g) << 8) | (b))
#define GX_RGB(r, g, b)      	 (((b) << 16) | ((g) << 8) | (r))
#define GX_RGB16(r, g, b)        (((b) << 10) | ((g) << 5) | (r))
#define GX_XY16(x, y)            (((y) << 8)  | (x))
#define GX_XY20(x, y)        	 (((y) << 10) | (x))
#define GX_XY24(x, y)            (((y) << 12) | (x))
#define GX_XY32(x, y)        	 (((y) << 16) | (x))
#define GX_F16(integer, frac)	 (((frac) << 8)  | (integer))
#define GX_F32(integer, frac)	 (((frac) << 16) | (integer))
#define GX_PACK_VEC2(v) 		 GX_XY32((v).x, (v).y)


/* Horizontal Display Modes */
#define GX_HRES_256 DMODE_HRES_256
#define GX_HRES_320 DMODE_HRES_320
#define GX_HRES_512 DMODE_HRES_512
#define GX_HRES_640 DMODE_HRES_640

/* Vertical Display Modes */
#define GX_VRES_240 DMODE_VRES_240
#define GX_VRES_480 DMODE_VRES_480


/* RGB Colors */
#define GX_WHITE    0xFFFFFF
#define GX_BLACK    0x000000
#define GX_GRAY     0x7F7F7F
#define GX_RED      0x0000FF
#define GX_GREEN    0x00FF00
#define GX_BLUE     0xFF0000
#define GX_CYAN     0xFFFF00


/* Typedefs to serve for easy understanding of parameters */
typedef uint32_t gx_xy32; // 32-bit x y coordinate (each component is 16 bits)
typedef uint32_t gx_xy20; // 20-bit x y coordinate (each component is 10 bits)
typedef uint16_t gx_f16; // 16-bit fixed-point decimal
typedef uint32_t gx_f32; // 32-bit fixed-point decimal
typedef uint32_t gx_rgb24; // 24-bit RGB color
typedef uint32_t gx_bgr24; // 24-bit BGR color
typedef uint32_t gx_texcoord; // Texture coordinate packed as 32-bit integer


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


/* Represents a texture in VRAM */
struct gx_texture;


/* Initializes the GPU and the library
 * hres corresponds to one of GX_HRES_*
 * vres corresponds to one of GX_VRES_*
 */
void GX_Init(uint8_t hres, uint8_t vres);


/* Get display resolution */
void GX_GetResolution(uint16_t *width, uint16_t *height);


/* Sets clear color */
void GX_SetClearColor(gx_rgb24 color);


/* Clears the framebuffer */
void GX_Clear(void);


/* Syncs to V-blank */
void GX_Sync(void);


/* Sets area to clip drawing to (optional) */
void GX_SetScissorRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h);


/* Copies a palette to VRAM
 *  clut_x determines where in VRAM to place the palette horizontally (clut_x * 16 = x offset)
 *  clut_y determines where in VRAM to place the palette vertically (clut_y = y offset)
 *  size is how many words are in the palette
 */
void GX_SetPalette(uint16_t clut_x, uint8_t clut_y, const uint32_t *palette, uint16_t size);


/* Copies an image to VRAM
 *  page_x is the horizontal page (page_x * 64 = x offset, 0 to 3)
 *  page_y is the vertical page  (page_y * 256 = y offset, 0 or 1)
 *  w is the width in half words (how many half words wide)
 *  h is the height in lines (how many lines tall)
 */
void GX_SetImage(
	uint32_t page_x,
	uint32_t page_y,
	const uint8_t *image,
	uint32_t w,
	uint32_t h
	);
 
 
 /* Loads a texture from a TIM file in RAM into VRAM */
struct gx_texture *GX_LoadTIM(const uint8_t *data);


/* Frees a texture from VRAM */
void GX_FreeTexture(struct gx_texture *tex);


/* Get texture's dimensions */
void GX_GetTextureDims(struct gx_texture *tex, uint16_t *w, uint16_t *h);


/* Sets the draw color */
void GX_SetDrawColor(gx_rgb24 color);


 /* Selects a texture for use in subsequent rendering operations */
void GX_SelectTexture(struct gx_texture *tex);


/* Draws a single color triangle */
void GX_DrawTriangleMonotone(gx_vec2_t v0, gx_vec2_t v1, gx_vec2_t v2);


/* Draws a single color quad
	Vertex order:
	v0--------------v1
	|                |
	|                |
	|                |
	|                |
	|                |
	|                |
	v2--------------v3
	
 */
void GX_DrawQuadMonotone(gx_vec2_t v0, gx_vec2_t v1, gx_vec2_t v2, gx_vec2_t v3);


/* Draws a single color rectangle (faster than quad) */
void GX_DrawRectangleMonotone(uint16_t x, uint16_t y, uint16_t w, uint16_t h);


/* Draws a textured rectangle (faster than quad) 
 *   u and v are the origin in the texture area
 */
void GX_DrawRectangleTextured(
	uint16_t x,
	uint16_t y,
	uint16_t w,
	uint16_t h,
	uint8_t u,
	uint8_t v
	);


#endif
