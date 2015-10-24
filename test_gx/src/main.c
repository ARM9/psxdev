#include <psx/gx.h>

int main(void)
{
	GX_Init();
	
	while (1)
	{
		gx_vec2_t v0 = { 50, 50 };
		gx_vec2_t v1 = { 50, 100 };
		gx_vec2_t v2 = { 100, 50 };
		gx_vec2_t v3 = { 100, 100 };
		GX_DrawQuad_SingleColor(v0, v1, v2, v3, GX_RGB(0, 255, 255));

		GX_Sync();
    }
	
    return 0;
}
