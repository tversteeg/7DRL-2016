#pragma once

#include "char.h"

#define NPCS_PER_TILE 0.01

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

void moveCharMap(map_t *m, char_t *c);

tile_t *getTile(const map_t *m, int x, int y);
char getCharFromTile(const tile_t *t);
