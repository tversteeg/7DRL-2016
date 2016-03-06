#include "map.h"

#include <stdlib.h>

map_t generateMap(int width, int height)
{
	map_t map = {.width = width, .height = height};
	map.t = (tile_t*)calloc(width * height, sizeof(tile_t));

	return map;
}

tile_t *getTile(const map_t *m, int x, int y)
{
	if(x < 0 || y < 0 || x >= m->width || y >= m->height){
		return NULL;
	}

	return &m->t[x + y * m->width];
}

char getCharFromTile(const tile_t *t)
{
	switch(t->type){
		case TILE_GRASS:
			return '.';
			break;
		case TILE_TREE:
			return '%';
			break;
		case TILE_BOULDER:
			return '*';
			break;
		default:
			return ' ';
	}
}
