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
