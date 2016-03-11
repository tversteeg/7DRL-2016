#include "map.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a > _b ? _a : _b; })
#define min(a,b) \
   ({ __typeof__ (a) _a = (a); \
       __typeof__ (b) _b = (b); \
     _a < _b ? _a : _b; })

static void createRoom(map_t *m, int x, int y)
{
	int width = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;
	int height = rand() % (MAX_ROOM_SIZE - MIN_ROOM_SIZE) + MIN_ROOM_SIZE;

	int sx = max(x - width / 2, 0);
	int ex = min(x + width / 2, m->width - 1);
	int sy = max(y - height / 2, 0);
	int ey = min(y + height / 2, m->height - 1);

	// Create layout
	for(int i = sy; i <= ey; i++){
		for(int j = sx; j <= ex; j++){
			m->t[i * m->width + j].type = TILE_FLOOR;
		}
	}

	int size = width * height;

	// Spawn random corridors
	int ncorridors = rand() % MAX_CORRIDORS_PER_ROOM + 1;
	for(int i = 0; i < ncorridors; i++){
		int ind = rand() % size;
		int cx = sx + ind % width;
		int cy = sy + ind / width;

		// Choose wall for the corridor
		tiletype_t type;
		switch(rand() % 4){
			case 0:
				cx = sx;
				type = TILE_WIP_CORRIDOR_WEST;
				break;
			case 1:
				cx = ex;
				type = TILE_WIP_CORRIDOR_EAST;
				break;
			case 2:
				cy = sy;
				type = TILE_WIP_CORRIDOR_NORTH;
				break;
			case 3:
				cy = ey;
				type = TILE_WIP_CORRIDOR_SOUTH;
				break;
		}

		m->t[cx + cy * m->width].type = type;
	}

	// Spawn enemies
	int enemies = size * MAX_ENEMIES_PER_TILE;

	int se = m->nc;
	m->nc += enemies;
	m->c = (char_t*)realloc(m->c, m->nc * sizeof(char_t));

	for(int i = se; i < m->nc; i++){
		char_t *c = m->c + i;
		int ind = rand() % size;
		c->x = sx + ind % width;
		c->y = sy + ind / width;
		c->tile = NULL;
		while(getCharMap(m, c->x, c->y) != NULL){
			c->x++;
			if(c->x >= ex){
				c->x = sx;
				c->y++;
				if(c->y >= ey){
					c->y = sy;
				}
			}
		}

		c->type = rand() % (CHAR_RAT - CHAR_WARRIOR + 1);
		setDefaultStats(c);

		moveCharMap(m, c, c->x, c->y);
	}
}

static void createRooms(map_t *m)
{
	// Find corridor ends
	int nt = m->width * m->height;
	for(int i = 0; i < nt; i++){
		if(m->t[i].type == TILE_WIP_ROOM){
			createRoom(m, i % m->width, i / m->width);
		}
	}
}

static void createCorridor(map_t *m, int i, int xd, int yd)
{
	int size = rand() % (MAX_CORRIDOR_SIZE - MIN_CORRIDOR_SIZE) + MIN_CORRIDOR_SIZE;

	int ya = yd * m->width;
	for(int c = 0; c < size; c++){
		m->t[i].type = TILE_FLOOR;
		i += xd + ya;
	}

	m->t[i].type = TILE_WIP_ROOM;
}

static void createCorridors(map_t *m)
{
	// Find corridor start points
	int nt = m->width * m->height;
	for(int i = 0; i < nt; i++){
		switch(m->t[i].type){
			case TILE_WIP_CORRIDOR_WEST:
				createCorridor(m, i, -1, 0);
				break;
			case TILE_WIP_CORRIDOR_EAST:
				createCorridor(m, i, 1, 0);
				break;
			case TILE_WIP_CORRIDOR_NORTH:
				createCorridor(m, i, 0, -1);
				break;
			case TILE_WIP_CORRIDOR_SOUTH:
				createCorridor(m, i, 0, 1);
				break;
			default: break;
		}
	}
}

map_t generateMap(int width, int height)
{
	int nt = width * height;

	map_t map = {.width = width, .height = height, .nc = 0};
	map.t = (tile_t*)calloc(nt, sizeof(tile_t));

	for(int i = 0; i < nt; i++){
		map.t[i].c = NULL;
	}

	map.t[width / 2 + (height / 2) * width].type = TILE_WIP_ROOM;

	for(int i = 0; i < MAP_ITERATIONS; i++){
		createRooms(&map);
		createCorridors(&map);
	}

	map.c[0].type = CHAR_PLAYER;
	setDefaultStats(map.c);

	return map;
}

movereturn_t moveCharMap(map_t *m, char_t *c, int x, int y)
{
	if(x < 0 || y < 0 || x >= m->width || y >= m->height){
		return MOVE_RETURN_OOB;
	}

	tile_t *t = &m->t[x + y * m->width];
	if(t->type != TILE_FLOOR){
		return MOVE_RETURN_WALL;
	}
	if(t->c != NULL){
		return MOVE_RETURN_ENEMY;
	}

	if(c->tile != NULL){
		((tile_t*)c->tile)->c = NULL;
	}
	t->c = c;
	c->tile = t;
	c->x = x;
	c->y = y;

	return MOVE_RETURN_REACHED;
}

void removeCharMap(map_t *m, char_t *c)
{
	if(c->tile != NULL){
		((tile_t*)c->tile)->c = NULL;
	}
	//TODO Remove from array
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
		case TILE_FLOOR:
			return '.';
			break;
		case TILE_WALL:
			return '%';
			break;
		case TILE_DOOR:
			return 'D';
			break;
		default:
			return ' ';
	}
}
