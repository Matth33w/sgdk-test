#include <genesis.h>
#include <resources.h>

Sprite *player;
s16 playerX = 128;
s16 playerY = 128;

s16 playerHorizontalSpeed = 0;
s16 playerVerticalSpeed = 0;

s16 playerSpeed = 3;

u16 inputValue = 0;

void directionHandler()
{
	playerX += playerHorizontalSpeed;
	playerY += playerVerticalSpeed;
}

void inputHandler(u16 joy, u16 changed, u16 state)
{
	if (joy == JOY_1) {
		if (state & BUTTON_RIGHT) {
			playerHorizontalSpeed = 2;
		} else if (state & BUTTON_LEFT) {
			playerHorizontalSpeed = -2;
		} else {
			if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT)) {
				playerHorizontalSpeed = 0;
			}
		}

		if (state & BUTTON_UP) {
			playerVerticalSpeed = -2;
		} else if (state & BUTTON_DOWN) {
			playerVerticalSpeed = 2;
		} else {
			if ((changed & BUTTON_UP) | (changed & BUTTON_DOWN)) {
				playerVerticalSpeed = 0;
			}
		}
	}
}

int main()
{
	SPR_init();
	JOY_init();
	VDP_setPalette(PAL1, witch.palette->data);
	player = SPR_addSprite(&witch, playerX, playerY, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
	VDP_setBackgroundColor(0);
	JOY_setEventHandler(inputHandler);
	while (1)
	{
		directionHandler();
		SPR_setPosition(player, playerX, playerY);
		SPR_update();
		SYS_doVBlankProcess();
	}
	return (0);
}