#include "gui.h"

#include <stdio.h>

#include "world.h"
#include "../window.h"

int getGuiWidth()
{
	return 20;
}

int getGuiHeight()
{
	return 20;
}

void renderGui(int x, int y)
{
	const char_t *p = getPlayer();

	char buf[20];
	sprintf(buf, "STR:%d", p->stats.strength);
	
	drawString(x, y + 1, buf, 255, 255, 255);

	sprintf(buf, "DEF:%d", p->stats.defence);
	drawString(x, y + 2, buf, 255, 255, 255);

	sprintf(buf, "LIF:%d/%d", p->stats.health, p->stats.max_health);
	drawString(x, y + 3, buf, 255, 255, 255);

	int dis;
	const char_t *e = getNearestEnemy(&dis);
	sprintf(buf, "Enemy:%s", getNameFromChar(e));
	drawString(x, y + 6, buf, 255, 255, 255);
}
