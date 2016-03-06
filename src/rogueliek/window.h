#pragma once

#include <stdbool.h>

void createWindow(const char *title, int width, int height);
void destroyWindow();

bool updateWindow();
void renderWindow(int ms);

void hideCursor();
void showCursor();

int pickFontFromDir(const char *dir);

void drawChar(int x, int y, char c, unsigned char r, unsigned char g, unsigned char b);
void drawString(int x, int y, const char *text, unsigned char r, unsigned char g, unsigned char b);
void drawCharBack(int x, int y, unsigned char r, unsigned char g, unsigned char b);
void drawPng(int id, int x, int y);
void drawPngName(const char *name, int x, int y);

void clear();

int getWidth();
int getHeight();
