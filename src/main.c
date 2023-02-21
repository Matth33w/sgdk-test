#include <genesis.h>
#include <resources.h>

#define CAMERA_WIDTH 320
#define CAMERA_HEIGHT 240
#define RIGHT_EDGE 320
#define BOTTOM_EDGE 240

Sprite *player;

s16 playerX = 128;
s16 playerY = 128;

s16 cameraX = 0;
s16 cameraY = 0;

s16 playerHorizontalSpeed = 0;
s16 playerVerticalSpeed = 0;

s16 playerSpeed = 3;
u16 ind;
u16 inputValue = 0;

u16 xOffset = 8;

Map *map;

typedef struct {
	Sprite* playerSprite;
	u16 x;
	u16 y;
} Player;

void directionHandler()
{
	playerX += playerHorizontalSpeed;
	playerY += playerVerticalSpeed;
}

void inputHandler(u16 joy, u16 changed, u16 state)
{
	if (joy == JOY_1) {
		if(state & BUTTON_A) {
			playerSpeed = 1;
		} else if(changed & BUTTON_A) {
			playerSpeed = 3;
		}

		if (state & BUTTON_RIGHT) {
			playerHorizontalSpeed = playerSpeed;
		} else if (state & BUTTON_LEFT) {
			playerHorizontalSpeed = -playerSpeed;
		} else {
			if ((changed & BUTTON_RIGHT) | (changed & BUTTON_LEFT)) {
				playerHorizontalSpeed = 0;
			}
		}

		if (state & BUTTON_UP) {
			playerVerticalSpeed = -playerSpeed;
		} else if (state & BUTTON_DOWN) {
			playerVerticalSpeed = playerSpeed;
		} else {
			if ((changed & BUTTON_UP) | (changed & BUTTON_DOWN)) {
				playerVerticalSpeed = 0;
			}
		}
	}
}

void loadBackground() {
	VDP_setPalette(PAL0, background_map.palette->data);
	ind = TILE_USERINDEX;
	VDP_loadTileSet(&background_tileset, ind, DMA);
	ind += background_tileset.numTile;
	map = MAP_create(&background_map, BG_A, TILE_ATTR_FULL(PAL0, FALSE, FALSE, FALSE, TILE_USERINDEX));
}

void setBackgroundOffset() {
	if(xOffset >= 128) {
		xOffset = 0;
	}

	xOffset += 1;
}

void playerPositionLimiter() {
	playerX = clamp(playerX, 0, RIGHT_EDGE - 40);
	playerY = clamp(playerY, 0, BOTTOM_EDGE - 48);
}

int main()
{
	SPR_init();
	JOY_init();
	loadBackground();
	VDP_setBackgroundColor(0);
	JOY_setEventHandler(inputHandler);
	VDP_setPalette(PAL2, witch.palette->data);
	XGM_startPlay(demo_music);
	player = SPR_addSprite(&witch, playerX, playerY, TILE_ATTR(PAL2, TRUE, FALSE, FALSE));
	while (1)
	{
		directionHandler();
		playerPositionLimiter();
		setBackgroundOffset();
		MAP_scrollTo(map, xOffset,0);
		SPR_setPosition(player, playerX, playerY);
		SPR_update();
		SYS_doVBlankProcess();
	}
	return (0);
}