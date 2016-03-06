#include "map.h"

#include <stdlib.h>

map_t generateMap(int width, int height)
{
	map_t map = {.width = width, .height = height};
	map.t = (tile_t*)calloc(width * height, sizeof(tile_t));

	for(int i = 0; i < width * height; i++){
		map.t[i].c = NULL;
	}

	return map;
}

void moveCharMap(map_t *m, char_t *c)
{
	if(c->x < 0 || c->y < 0 || c->x >= m->width || c->y >= m->height){
		return;
	}

	tile_t *t = &m->t[c->x + c->y * m->width];
	c->tile = t;
	t->c = c;
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
	if(t == NULL){
		return ' ';
	}else if(t->c != NULL){
		return getCharFromChar(t->c); 
	}
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
