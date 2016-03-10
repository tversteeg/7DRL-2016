#pragma once

#include <stdbool.h>

#include "stats.h"

typedef enum {
	CHAR_WARRIOR = 0,
	CHAR_ARCHER,
	CHAR_SORCERER,
	CHAR_SKELETON,
	CHAR_RAT,
	CHAR_NPC,
	CHAR_PLAYER
} chartype_t;

typedef struct {
	stats_t stats;
	chartype_t type;
	int x, y;
	void *tile; // Can't use tile_t because of a circular reference
} char_t;

char getCharFromChar(const char_t *c);
const char *getNameFromChar(const char_t *c);

int getDamage(const char_t *source, const char_t *target);
bool doDamage(char_t *c, int damage);

int getLevelForXP(int xp);

void setDefaultStats(char_t *c);
