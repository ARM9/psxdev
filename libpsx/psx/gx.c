#include <psx/gpu.h>
#include <psx/gx.h>

#define GX_DRAWMODE_DISPLAY GX_BIT(10)

void GX_Init(void)
{
	// Bootstrap
	GP1_DO(ResetGpu, 0);
	GP1_DO(EnableDisplay, 0);
	
	// Drawing to display
	GP0_DO(DrawMode, GX_DRAWMODE_DISPLAY);

	// Required for timing stuff
	GP0NOP;
}

void GX_SetScissorRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h)
{
	GP0_DO(DrawAreaTopLeft,     GX_XY20(x, y));
    GP0_DO(DrawAreaBottomRight, GX_XY20(x + w, y + h));
}

void GX_Sync(void)
{
	waitVblank();
	GP1_DO(DmaDirection, 0);
	GP1_DO(ResetCommandBuffer, 0);
	GP0_DO(ClearCache, 0);
}

void GX_FillRect(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint32_t color)
{
	GP0_DO(FillRectVram, color);
	GP[0] = GX_XY32(x, y);
	GP[0] = GX_XY32(w, h);
}
