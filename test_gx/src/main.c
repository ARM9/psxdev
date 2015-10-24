#include <psx/gx.h>

int main(void)
{
	GX_Init();
	while (1)
	{
		GX_FillRect(100, 100, 80, 60, GX_RGB(0, 255, 255));
		GX_Sync();
    }
    return 0;
}
