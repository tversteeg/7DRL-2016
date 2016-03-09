#include "char.h"

#define SWITCH_CHAR(name, ret) \
	case name: return ret; break;

char getCharFromChar(const char_t *c)
{
	switch(c->type){
		SWITCH_CHAR(CHAR_PLAYER, '@')
		SWITCH_CHAR(CHAR_WARRIOR, 'w')
		SWITCH_CHAR(CHAR_ARCHER, 'a')
		SWITCH_CHAR(CHAR_SORCERER, 's')
		SWITCH_CHAR(CHAR_SKELETON, 'u')
		SWITCH_CHAR(CHAR_RAT, 'r')
		SWITCH_CHAR(CHAR_NPC, 'N')
		default:
			return ' ';
	}
}

const char *getNameFromChar(const char_t *c)
{
	switch(c->type){
		SWITCH_CHAR(CHAR_PLAYER, "Player")
		SWITCH_CHAR(CHAR_WARRIOR, "Warrior")
		SWITCH_CHAR(CHAR_ARCHER, "Archer")
		SWITCH_CHAR(CHAR_SORCERER, "Sorcerer")
		SWITCH_CHAR(CHAR_SKELETON, "Skeleton")
		SWITCH_CHAR(CHAR_RAT, "Rat")
		SWITCH_CHAR(CHAR_NPC, "NPC")
		default:
			return "Undefined";
	}
}

#undef SWITCH_CHAR
#define SWITCH_CHAR(name, str, def, maxh) \
	case name:\
		stats.strength = str;\
		stats.defence = def;\
		stats.max_health = maxh;\
		break;

void setDefaultStats(char_t *c)
{
	stats_t stats = {0};

	switch(c->type){
		SWITCH_CHAR(CHAR_PLAYER, 2, 2, 100)
		SWITCH_CHAR(CHAR_WARRIOR, 10, 10, 10)
		SWITCH_CHAR(CHAR_ARCHER, 10, 0, 4)
		SWITCH_CHAR(CHAR_SORCERER, 10, 0, 3)
		SWITCH_CHAR(CHAR_SKELETON, 3, 5, 15)
		SWITCH_CHAR(CHAR_RAT, 1, 0, 2)
		SWITCH_CHAR(CHAR_NPC, 0, 0, -1)
	}

	stats.health = stats.max_health;

	c->stats = stats;
}

#undef SWITCH_CHAR
