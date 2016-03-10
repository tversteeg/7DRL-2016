#include "world.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#include <ccore/event.h>

#include "map.h"
#include "gui.h"
#include "../window.h"

map_t map;

int turn;
bool redraw;
char_t *nearest;
int ndis;

static void die()
{
	popupText("");
	popupText("");
	popupText("");
	popupText("You got killed!");
}

static void endTurn()
{
	// Regain some life
	if(turn % 10 == 0 && getPlayer()->stats.health < getPlayer()->stats.max_health){
		getPlayer()->stats.health++;
	}

	redraw = true;
	nearest = NULL;

	turn++;
}

static void checkLevelUp()
{
	char buf[50];

	int oldlvl = getPlayer()->stats.level;
	int newlvl = getLevelForXP(getPlayer()->stats.xp);
	while(++oldlvl <= newlvl){
		sprintf(buf, "Level up: %d!", oldlvl);
		popupText(buf);

		if(newlvl % 2 == 0){
			getPlayer()->stats.defence++;
			getPlayer()->stats.strength++;
		}

		getPlayer()->stats.max_health += 2;
		getPlayer()->stats.health += 2;
	}

	getPlayer()->stats.level = newlvl;
}

static void fight(char_t *c)
{
	// Always hit the enemy first
	int damage = getDamage(getPlayer(), c);

	char buf[50];
	if(!doDamage(c, damage)){
		getPlayer()->stats.xp += c->stats.xp;
		removeCharMap(&map, c);

		sprintf(buf, "You killed \"%s\"", getNameFromChar(c));
		popupText(buf);

		checkLevelUp();
		return;
	}else{
		sprintf(buf, "You deal %d damage", damage);
		popupText(buf);
	}

	damage = getDamage(c, getPlayer());
	sprintf(buf, "You take %d damage", damage);
	popupText(buf);
	if(!doDamage(getPlayer(), damage)){
		getPlayer()->stats.health = 0;
		die();
	}
}

static void movePlayer(int x, int y)
{
	char_t *p = getPlayer();
	if(p->stats.health <= 0){
		return;
	}

	if(moveCharMap(&map, p, p->x + x, p->y + y) == TILE_ENEMY){
		tile_t *t = getTile(&map, p->x + x, p->y + y);

		fight(t->c);
	}else{
		popupText("");
	}

	endTurn();
}

void initWorld()
{
	srand(time(NULL));

	map = generateMap(MAP_WIDTH, MAP_HEIGHT);

	redraw = true;
	turn = 0;
	nearest = NULL;
}

bool updateWorld()
{
	return redraw;
}

void renderWorld(int vx, int vy, int vwidth, int vheight)
{
	if(!redraw){
		return;
	}

	clear();

	const char_t *p = getPlayer();
	int dmgcol = 255;
	if(p->stats.health < p->stats.max_health / 2){
		dmgcol = p->stats.health / ((float)p->stats.max_health) * 512;
	}

	int dis;
	const char_t *n = getNearestEnemy(&dis);

	for(int x = 0; x < vwidth; x++){
		for(int y = 0; y < vheight; y++){
			int rx = p->x + x - vwidth / 2;
			int ry = p->y + y - vheight / 2;
			tile_t *t = getTile(&map, rx, ry);
			char c = getCharFromTile(t);

			int nearestc = 1;
			if(t->c == n){
				nearestc = 0;
			}
			
			if(p->stats.health <= 0){
				drawCharBack(x + vx, y + vy, 64, 0, 0);
				drawChar(x + vx, y + vy, c, 255, 0, 0);
			}else{
				drawChar(x + vx, y + vy, c, 255, dmgcol, dmgcol * nearestc);
			}
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
		*distance = ndis;
		return nearest;
	}

	*distance = 1000;
	for(int i = 1; i < map.nc; i++){
		char_t *e = map.c + i;
		if(e->stats.health <= 0){
			continue;
		}

		int dx = e->x - getPlayer()->x;
		int dy = e->y - getPlayer()->y;
		int dis = sqrt(dx * dx + dy * dy);
		if(dis < *distance){
			nearest = e;
			*distance = dis;
		}
	}

	ndis = *distance;

	return nearest;
}
