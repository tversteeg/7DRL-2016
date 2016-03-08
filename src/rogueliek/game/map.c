#include "map.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

map_t generateMap(int width, int height)
{
	int nt = width * height;

	map_t map = {.width = width, .height = height};
	map.t = (tile_t*)calloc(nt, sizeof(tile_t));

	for(int i = 0; i < nt; i++){
		map.t[i].c = NULL;
	}

	map.nc = nt * NPCS_PER_TILE;
	map.c = (char_t*)calloc(map.nc, sizeof(char_t));

	for(int i = 0; i < map.nc; i++){
		char_t *c = map.c + i;
		int ind = rand() % nt;
		c->x = ind % map.width;
		c->y = ind / map.width;
		while(getCharMap(&map, c->x, c->y) != NULL){
			c->x++;
			if(c->x >= map.width){
				c->x = 0;
				c->y++;
				if(c->y >= map.height){
					c->y = 0;
				}
			}
		}

		c->type = CHAR_WARRIOR;
		setDefaultStats(c);

		moveCharMap(&map, c);
	}

	map.c[0].type = CHAR_PLAYER;
	setDefaultStats(map.c);

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

char_t *getCharMap(map_t *m, int x, int y)
{
	if(x < 0 || y < 0 || x >= m->width || y >= m->height){
		return NULL;
	}

	tile_t *t = &m->t[x + y * m->width];

	return t->c;
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