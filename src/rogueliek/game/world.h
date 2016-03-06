#pragma once

#define MAP_WIDTH 10
#define MAP_HEIGHT 10

#define NPCS_PER_TILE 0.01

void initWorld();
void updateWorld();
void renderWorld(int vx, int vy, int vwidth, int vheight);
