#include <genesis.h>
#include <resources.h>

int main()
{
	SPR_init();
	Sprite* player;
	VDP_setPalette(PAL1, witch.palette->data);
	VDP_setBackgroundColor(0);
	player = SPR_addSprite(&witch, 60, 80, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
	VDP_drawText("Sega Genesis - Projeto Base", 6, 8);
	VDP_drawText("Programado por Matth33w", 6, 9);
	while(1)
	{        
		SPR_update();
		SYS_doVBlankProcess();
	}
	return (0);
}