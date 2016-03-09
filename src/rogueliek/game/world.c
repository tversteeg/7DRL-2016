#include "world.h"

#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <ccore/event.h>

#include "map.h"
#include "../window.h"

map_t map;

bool redraw;
char_t *nearest;

static void endTurn()
{
	redraw = true;
	nearest = NULL;
}

static void movePlayer(int x, int y)
{
	char_t *p = getPlayer();
	if(moveCharMap(&map, p, p->x + x, p->y + y) == TILE_ENEMY){
		// Attack enemy
	}

	endTurn();
}

void initWorld()
{
	srand(time(NULL));
	
	map = generateMap(MAP_WIDTH, MAP_HEIGHT);

	redraw = true;
}

void updateWorld()
{

}

void renderWorld(int vx, int vy, int vwidth, int vheight)
{
	if(!redraw){
		return;
	}

	clear();

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

	redraw = false;
}

void handleKeyDownWorld(int keycode)
{
	switch(keycode){
		case CC_KEY_W:
			movePlayer(0, -1);
			break;
		case CC_KEY_S:
			movePlayer(0, 1);
			break;
		case CC_KEY_A:
			movePlayer(-1, 0);
			break;
		case CC_KEY_D:
			movePlayer(1, 0);
			break;
	}
}

void handleKeyUpWorld(int keycode)
{

}

char_t *getPlayer()
{
	return map.c;
}

char_t *getNearestEnemy(int *distance)
{
	if(nearest != NULL){
		return nearest;
	}

	*distance = 1000;
	for(int i = 1; i < map.nc; i++){
		char_t *e = map.c + i;
		
		int dx = e->x - getPlayer()->x;
		int dy = e->y - getPlayer()->y;
		int dis = sqrt(dx * dx + dy * dy);
		if(dis < *distance){
			nearest = e;
			*distance = dis;
		}
	}

	return nearest;
}
