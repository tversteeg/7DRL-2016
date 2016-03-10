#pragma once

#include "char.h"

#define NPCS_PER_TILE 0.02

typedef enum {
	TILE_GRASS,
	TILE_TREE,
	TILE_BOULDER
} tiletype_t;

typedef struct {
	char_t *c;
	tiletype_t type;
} tile_t;

typedef struct {
	int width, height;
	tile_t *t;

	int nc;
	char_t *c;
} map_t;

map_t generateMap(int width, int height);

typedef enum {
	TILE_OOB,
	TILE_ENEMY,
	TILE_REACHED
} movereturn_t;
movereturn_t moveCharMap(map_t *m, char_t *c, int x, int y);
char_t *getCharMap(map_t *m, int x, int y);
void removeCharMap(map_t *m, char_t *c);

tile_t *getTile(const map_t *m, int x, int y);
char getCharFromTile(const tile_t *t);
