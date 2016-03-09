#pragma once

#include "char.h"

#define MAP_WIDTH 1024
#define MAP_HEIGHT 1024

void initWorld();
void updateWorld();
void renderWorld(int vx, int vy, int vwidth, int vheight);
void handleKeyDownWorld(int keycode);
void handleKeyUpWorld(int keycode);

char_t *getPlayer();
char_t *getNearestEnemy(int *distance);
