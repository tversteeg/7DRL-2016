#include "gui.h"

#include <stdio.h>
#include <string.h>

#include "world.h"
#include "../window.h"

char *(popup[MAX_POPUP]);
int top = 0;

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
	
	int yp = y;

	char buf[20];
	sprintf(buf, "HP :%d/%d", p->stats.health, p->stats.max_health);
	drawString(x, ++yp, buf, 255, 255, 255);

	sprintf(buf, "STR:%d", p->stats.strength);
	
	drawString(x, ++yp, buf, 255, 255, 255);

	sprintf(buf, "DEF:%d", p->stats.defence);
	drawString(x, ++yp, buf, 255, 255, 255);

	sprintf(buf, "XP :%d", p->stats.xp);
	drawString(x, ++yp, buf, 255, 255, 255);

	int dis;
	const char_t *e = getNearestEnemy(&dis);
	if(dis < 5){
		yp += 2;
		drawString(x, ++yp, "Enemy", 255, 255, 255);
		drawString(x, ++yp, getNameFromChar(e), 255, 255, 255);

		sprintf(buf, "HP :%d/%d", e->stats.health, e->stats.max_health);
		drawString(x, ++yp, buf, 255, 255, 255);
		yp += 2;
	}else{
		yp += 7;
	}

	for(int i = top - 1; i >= 0; i--){
		int shade = (i / (float)MAX_POPUP) * 255;
		drawString(x, ++yp, popup[i], shade, shade, shade);
	}
}

void popupText(const char *str)
{
	size_t len = strlen(str);
	if(len >= getGuiWidth()){
		popupText(str + getGuiWidth());
		len = getGuiWidth() - 1;
	}

	if(top < MAX_POPUP){
		popup[top] = (char*)malloc(getGuiWidth());
		top++;
	}else{
		for(int i = 1; i < top; i++){
			memcpy(popup[i - 1], popup[i], getGuiWidth());
		}
	}

	strncpy(popup[top - 1], str, len);
	popup[top - 1][len] = '\0';
}
