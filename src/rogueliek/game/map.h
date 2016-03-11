#pragma once

#include "char.h"

#define MAX_ENEMIES_PER_TILE 0.05
#define MAX_CORRIDORS_PER_ROOM 2
#define MAX_ROOM_SIZE 10
#define MIN_ROOM_SIZE 2

#define MAX_CORRIDOR_SIZE 10
#define MIN_CORRIDOR_SIZE 5

#define MAP_ITERATIONS 5

typedef enum {
	TILE_UNUSED = 0,
	TILE_WALL,
	TILE_FLOOR,
	TILE_DOOR,
	TILE_WIP_ROOM,
	TILE_WIP_CORRIDOR_WEST,
	TILE_WIP_CORRIDOR_EAST,
	TILE_WIP_CORRIDOR_NORTH,
	TILE_WIP_CORRIDOR_SOUTH
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
	MOVE_RETURN_OOB,
	MOVE_RETURN_ENEMY,
	MOVE_RETURN_WALL,
	MOVE_RETURN_REACHED
} movereturn_t;
movereturn_t moveCharMap(map_t *m, char_t *c, int x, int y);
char_t *getCharMap(map_t *m, int x, int y);
void removeCharMap(map_t *m, char_t *c);

tile_t *getTile(const map_t *m, int x, int y);
char getCharFromTile(const tile_t *t);
