#include <psx/gx.h>
#include "../res/kid.tim.c"

typedef struct sprite
{
	int occupied;
	int tx, ty; // Texture coordinates
	int x, y; // Position on screen
	uint8_t w, h; // Size
	int vx, vy; // Velocity
}
sprite_t;

uint16_t res_w;
uint16_t res_h;
struct gx_texture *texture;
uint16_t tex_w;
uint16_t tex_h;
sprite_t sprites[32];

sprite_t *InitSprite(int x, int y, int tx, int ty, int vx, int vy)
{
	for (int i = 0; i < 32; ++i)
	{
		sprite_t *spr = &sprites[i];
		if (!spr->occupied)
		{
			spr->occupied = 1;
			spr->x = x;
			spr->y = y;
			spr->vx = vx;
			spr->vy = vy;
			spr->tx = tx;
			spr->ty = ty;
			spr->w = tex_w;
			spr->h = tex_h;
			return spr;
		}
	}
	return 0;
}

void UpdateSprite(sprite_t *spr)
{
	int newx = spr->x + spr->vx;
	int newy = spr->y + spr->vy;
	spr->x=newx;
	spr->y=newy;
	
	if ((newx + spr->w) >= res_w || (newy + spr->h) >= res_h || newx <= 0 || newy <= 0)
	{
		int vx = spr->vx;
		spr->vx = -spr->vy;
		spr->vy = vx;
	}
	else
	{
		spr->x = newx;
		spr->y = newy;
	}
}

int main(void)
{
	GX_Init(GX_HRES_320, GX_VRES_240);
	
	GX_SetClearColor(GX_GRAY);
	
	GX_GetResolution(&res_w, &res_h);
	
	texture = GX_LoadTIM(kid_tim);
	GX_GetTextureDims(texture, &tex_w, &tex_h);
	
	for (int i = 0; i < 32; ++i)
		sprites[i].occupied = 0;

	InitSprite(50, 50, 0, 0, -1, 1);
	InitSprite(60, 30, 0, 0, 1, 1);
	InitSprite(120, 20, 0, 0, -1, -1);
	InitSprite(100, 80, 0, 0, 1, -1);
	
	while (1)
	{
		GX_Clear();
		
		GX_SelectTexture(texture);
		
		for (int i = 0; i < 32; ++i)
		{
			sprite_t *spr = &sprites[i];
			if (spr->occupied)
			{
				UpdateSprite(&sprites[i]);
				GX_DrawRectangleTextured(
					spr->x,
					spr->y,
					spr->w,
					spr->h,
					spr->tx,
					spr->ty
					);
			}
		}
		
		GX_Sync();
    }
	
    return 0;
}
