#include "world.h"

#include "map.h"
#include "../window.h"

map_t map;

void initWorld()
{
	map = generateMap(1024, 1024);
}

void updateWorld()
{

}

void renderWorld(int vx, int vy, int vwidth, int vheight)
{
	for(int x = 0; x < vwidth; x++){
		for(int y = 0; y < vheight; y++){
			tile_t *t = getTile(&map, x, y);
			char c = getCharFromTile(t);

			drawChar(x + vx, y + vy, c, 255, 255, 255);
		}
	}
}
