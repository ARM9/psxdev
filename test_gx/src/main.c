#include <psx/gx.h>

int main(void)
{
	GX_Init(0, 0, 640, 480);
	while (1)
	{
		GX_Sync();
		GX_FillRect(100, 100, 80, 60, GX_RGB(0, 255, 255));
    }
    return 0;
}
