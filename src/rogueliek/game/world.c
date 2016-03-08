#include "world.h"

#include <stdlib.h>
#include <time.h>
#include <stdlib.h>

#include "map.h"
#include "../window.h"

map_t map;

int nchars;
char_t *chars;

void initWorld()
{
	srand(time(NULL));
	
	map = generateMap(MAP_WIDTH, MAP_HEIGHT);
}

void updateWorld()
{

}

void renderWorld(int vx, int vy, int vwidth, int vheight)
{
	for(int x = 0; x < vwidth; x++){
		for(int y = 0; y < vheight; y++){
			const char_t *p = getPlayer();
			int rx = p->x + x - vwidth / 2;
			int ry = p->y + y - vheight / 2;
			tile_t *t = getTile(&map, rx, ry);
			char c = getCharFromTile(t);

			drawChar(x + vx, y + vy, c, 255, 255, 255);
		}
	}
}

char_t *getPlayer()
{
	return &map.c[0];
}
