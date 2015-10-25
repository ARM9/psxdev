/****************************************************************************
                          PSX GPU Graphics Wrapper
 ***************************************************************************/

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <limits.h>
#include <psx/gx.h>
#include <psx/interrupts.h>


/* Private utility macros */
#define GX_DRAWMODE_DISPLAY GX_BIT(10)
#define GX_MAX_TEXTURES 16
#define GX_CLUT(x, y) (x | (y << 6))


/* gx_texture */
typedef struct gx_texture
{
	uint32_t occupied;
	uint32_t clut_x, clut_y;
	uint32_t texpage_x, texpage_y;
	uint32_t texpage_mode;
	uint16_t width;
	uint16_t height;
}
gx_texture_t;


/* Internal state */
static uint16_t gx_res_w;
static uint16_t gx_res_h;
static gx_rgb24 gx_clear_color;
static gx_rgb24 gx_draw_color;
static gx_texture_t gx_textures[GX_MAX_TEXTURES];
static gx_texture_t *gx_active_texture;


/* Determine width in pixels of display mode */
static int GetHResWidth(uint8_t hres)
{
	switch (hres)
	{
	case GX_HRES_256: return 256;
	case GX_HRES_320: return 320;
	case GX_HRES_512: return 512;
	case GX_HRES_640: return 640;
	}
	return 0;
}

/* Determine height in pixels of display mode */
static int GetVResHeight(uint8_t vres)
{
	switch (vres)
	{
	case GX_VRES_240: return 240;
	case GX_VRES_480: return 480;
	}
	return 0;
}


//----------------------------------------------------------------------------
// GX_Init
//----------------------------------------------------------------------------
void GX_Init(uint8_t hres, uint8_t vres)
{
	// Bootstrap
	GP1_DO(ResetGpu, 0);
	GP1_DO(EnableDisplay, 0);
	
	// Drawing to display
	GP0_DO(DrawMode, GX_DRAWMODE_DISPLAY);
	
	// Set display mode
	GP1_DO(DisplayMode, (vres << 2) | hres);
	gx_res_w = GetHResWidth(hres);
	gx_res_h = GetVResHeight(vres);
	
	// Setup initial scissor
	GX_SetScissorRect(0, 0, gx_res_w, gx_res_h);

	// Initially we draw in white
	GX_SetDrawColor(0xFFFFFF);
	
	// Clear to black
	GX_SetClearColor(0x000000);
	
	uint8_t i;
	for (i = 0; i < GX_MAX_TEXTURES; ++i)
		gx_textures[i].occupied = 0;
	
	gx_active_texture = 0;
}

//----------------------------------------------------------------------------
// GX_GetResolution
//----------------------------------------------------------------------------
void GX_GetResolution(uint16_t *width, uint16_t *height)
{
	if (width) *width = gx_res_w;
	if (height) *height = gx_res_h;
}

//----------------------------------------------------------------------------
// GX_SetClearColor
//----------------------------------------------------------------------------
void GX_SetClearColor(gx_rgb24 color)
{
	gx_clear_color = color;
}

//----------------------------------------------------------------------------
// GX_Clear
//----------------------------------------------------------------------------
void GX_Clear(void)
{
	GP0_DO(FillRectVram, gx_clear_color);
	GP[0] = GX_XY32(0, 0);
	GP[0] = GX_XY32(gx_res_w, gx_res_h);
}

//----------------------------------------------------------------------------
// GX_Sync
//----------------------------------------------------------------------------
void GX_Sync(void)
{
	waitVblank();
	GP1_DO(ResetCommandBuffer, 0);
}

//----------------------------------------------------------------------------
// GX_SetScissorRect
//----------------------------------------------------------------------------
void GX_SetScissorRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	GP0_DO(DrawAreaTopLeft,     GX_XY20( x,   y   ));
	GP0_DO(DrawAreaBottomRight, GX_XY20( x+w, y+h ));
	GP0NOP;
}

//----------------------------------------------------------------------------
// GX_SetPalette
//----------------------------------------------------------------------------
void GX_SetPalette(uint16_t clut_x, uint8_t clut_y, const uint32_t *palette, uint16_t size)
{
	GP0_DO(CopyRectCpuVram, 0);
	GP[0] = GX_XY32(clut_x << 4, clut_y);
	GP[0] = GX_XY32(size << 1, 1);
	// TODO: Replace with efficient DMA transfer
	uint16_t i;
	for (i = 0; i < size; ++i)
		GP[0] = palette[i];
}

//----------------------------------------------------------------------------
// GX_SetImage
//----------------------------------------------------------------------------
void GX_SetImage(
	uint32_t page_x,
	uint32_t page_y,
	const uint8_t *image,
	uint32_t w,
	uint32_t h
	)
{
	GP0_DO(CopyRectCpuVram, 0);
	GP[0] = GX_XY32(0, page_y << 8);
	GP[0] = GX_XY32(w >> 1, h);
	// TODO: Replace with efficient DMA transfer
	for (uint32_t i = 0, s = w * h; i < s; i += 4)
		GP[0] = *((uint32_t*)&image[i]);
}

/* Reads a 32-bit integer from a memory buffer */
static uint32_t ReadU32(const uint8_t **buf)
{
	uint32_t x = *((uint32_t*)*buf);
	(*buf) += 4;
	return x;
}

/* TIM flags */
#define TIM_CF GX_BIT(3) // CLUT flag

/* Reads a TIM image from RAM to VRAM */
static int ReadTIM(const uint8_t *in, gx_texture_t *out)
{
	const uint8_t *p = in;
	
	uint32_t id = ReadU32(&p);
	if (id != 0x10)
	{
		printf("Invalid TIM ID! (%d)\n", id);
		return 0;
	}
	
	uint32_t flag = ReadU32(&p);
	uint8_t mode = flag & GX_BITS(3);
	uint8_t hasCLUT = (flag & TIM_CF) ? 1 : 0;
	
	if (mode != 0x01)
	{
		printf("Non 8-bit TIMs are not supported at the moment (mode=%d)\n", mode);
		return 0;
	}
	
	// Read CLUT
	if (hasCLUT)
	{
		uint32_t *clutOrigin = p;
		uint32_t clutSize = ReadU32(&p); // size of the CLUT section
		uint32_t offset = ReadU32(&p); // x, y
		uint32_t size = ReadU32(&p); // width, height
		uint32_t width = (size & GX_BITS(16)) << 1;
		uint32_t height = size >> 16;
		out->clut_x = 20;
		out->clut_y = 0;
		GX_SetPalette(out->clut_x, out->clut_y, p, width >> 1);
		p = clutOrigin + (clutSize >> 2);
		printf("CLUT loaded (%dx%d)\n", width, height);
	}
	
	// Read image
	{
		ReadU32(&p); // size of the image section
		uint32_t offset = ReadU32(&p); // x, y
		uint32_t size = ReadU32(&p); // width, height
		out->texpage_x = 0;
		out->texpage_y = 1;
		out->width = (size & GX_BITS(16)) << 1;
		out->height = size >> 16;
		out->texpage_mode = mode;
		GX_SetImage(out->texpage_x, out->texpage_y, p, out->width, out->height);
		printf("TIM loaded (%dx%d)\n", out->width, out->height);
	}
	
	return 1;
}

//----------------------------------------------------------------------------
// GX_LoadTIM
//----------------------------------------------------------------------------
struct gx_texture *GX_LoadTIM(const uint8_t *data)
{
	int i;
	gx_texture_t *tex;
	for(i = 0; i < GX_MAX_TEXTURES; ++i)
	{
		tex = &gx_textures[i];
		if (!tex->occupied)
		{
			if (ReadTIM(data, tex))
			{
				tex->occupied = 1;
				return tex;
			}
			break;
		}
	}
	printf("Texture limit exhaused (limit: %d)\n", GX_MAX_TEXTURES);
	return 0;
}

//----------------------------------------------------------------------------
// GX_FreeTexture
//----------------------------------------------------------------------------
void GX_FreeTexture(struct gx_texture *tex)
{
	tex->occupied = 0;
}

//----------------------------------------------------------------------------
// GX_GetTextureDims
//----------------------------------------------------------------------------
void GX_GetTextureDims(struct gx_texture *tex, uint16_t *w, uint16_t *h)
{
	if (w) *w = tex->width;
	if (h) *h = tex->height;
}

//----------------------------------------------------------------------------
// GX_SetDrawColor
//----------------------------------------------------------------------------
void GX_SetDrawColor(gx_rgb24 color)
{
	gx_draw_color = color;
}

//----------------------------------------------------------------------------
// GX_SelectTexture
//----------------------------------------------------------------------------
void GX_SelectTexture(struct gx_texture *tex)
{
	if (gx_active_texture == tex) return; // Is this any good?
	uint32_t drawMode = GX_DRAWMODE_DISPLAY;
	drawMode |= (tex->texpage_x << 0);
	drawMode |= (tex->texpage_y << 4);
	drawMode |= (tex->texpage_mode << 7);
	GP0_DO(DrawMode, drawMode);
	gx_active_texture = tex;
}

//----------------------------------------------------------------------------
// GX_DrawTriangleMonotone
//----------------------------------------------------------------------------
void GX_DrawTriangleMonotone(
	gx_vec2_t v0,
	gx_vec2_t v1,
	gx_vec2_t v2
	)
{
	GP0_DO(FlatTriOpaque, gx_draw_color);
	GP[0] = GX_PACK_VEC2(v0);
	GP[0] = GX_PACK_VEC2(v1);
	GP[0] = GX_PACK_VEC2(v2);
}

//----------------------------------------------------------------------------
// GX_DrawQuadMonotone
//----------------------------------------------------------------------------
void GX_DrawQuadMonotone(
	gx_vec2_t v0,
	gx_vec2_t v1,
	gx_vec2_t v2,
	gx_vec2_t v3
	)
{
	GP0_DO(FlatQuadOpaque, gx_draw_color);
	GP[0] = GX_PACK_VEC2(v0);
	GP[0] = GX_PACK_VEC2(v1);
	GP[0] = GX_PACK_VEC2(v2);
	GP[0] = GX_PACK_VEC2(v3);
}

//----------------------------------------------------------------------------
// GX_DrawRectangleMonotone
//----------------------------------------------------------------------------
void GX_DrawRectangleMonotone(
	uint16_t x, 
	uint16_t y,
	uint16_t w,
	uint16_t h
	)
{
	GP0_DO(FlatRectVarOpaque, gx_draw_color);
	GP[0] = GX_XY32(x, y);
	GP[0] = GX_XY32(w, h);
}

//----------------------------------------------------------------------------
// GX_DrawRectangleTextured
//----------------------------------------------------------------------------
void GX_DrawRectangleTextured(
	uint16_t x,
	uint16_t y,
	uint16_t w,
	uint16_t h,
	uint8_t u,
	uint8_t v
	)
{
	GP0_DO(TexRectVarOpaqueRaw, gx_draw_color);
	GP[0] = GX_XY32(x, y);
	GP[0] = (GX_CLUT(gx_active_texture->clut_x, gx_active_texture->clut_y) << 16) | GX_XY16(u, v);
	GP[0] = GX_XY32(w, h);
}



