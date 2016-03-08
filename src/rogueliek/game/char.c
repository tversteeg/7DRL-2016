#include "char.h"

char getCharFromChar(const char_t *c)
{
	switch(c->type){
		case CHAR_PLAYER:
			return '@';
			break;
		case CHAR_WARRIOR:
			return 'w';
			break;
		case CHAR_NPC:
			return 'n';
			break;
		default:
			return ' ';
	}
}

void setDefaultStats(char_t *c)
{
	stats_t stats = {0};

	switch(c->type){
		case CHAR_PLAYER:
			stats.strength = 2;
			stats.defence = 2;
			stats.max_health = 100;
			break;
		case CHAR_WARRIOR:
			stats.strength = 10;
			stats.defence = 10;
			stats.max_health = 5;
			break;
		case CHAR_NPC:
			stats.strength = 0;
			stats.defence = 0;
			stats.max_health = -1;
			break;
	}

	stats.health = stats.max_health;

	c->stats = stats;
}
