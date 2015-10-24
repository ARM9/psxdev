#include <psx/gx.h>

int main(void)
{
	GX_Init();
	
	while (1)
	{
		gx_vec2_t v0 = { 50, 50 };
		gx_vec2_t v1 = { 150, 50 };
		gx_vec2_t v2 = { 100, 150 };
		GX_DrawTriangle_SingleColor(v0, v1, v2, GX_RGB(0, 255, 255));

		GX_Sync();
    }
	
    return 0;
}
