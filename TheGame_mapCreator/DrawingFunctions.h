#pragma once

#include <SDL.h>

void putPixel(SDL_Surface *dest, int x, int y, int r, int g, int b);
void swapValue(int* a, int* b);
void drawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1, int r, int g, int b);
void drawBoldLine(SDL_Surface* dest, int x0, int y0, int x1, int y1, int size, int r, int g, int b);