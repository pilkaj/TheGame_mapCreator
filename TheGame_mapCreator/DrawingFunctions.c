#include "DrawingFunctions.h"

void putPixel(SDL_Surface *dest, int x, int y, int r, int g, int b)
{
	if (x >= 0 && x < dest->w && y >= 0 && y < dest->h)
		((Uint32*)dest->pixels)[y*dest->pitch/4 + x] = SDL_MapRGB(dest->format, r, g, b);
}

void swapValue(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

void drawLine(SDL_Surface* dest, int x0, int y0, int x1, int y1, int r, int g, int b)
{
	int step = abs(x1 - x0) < abs(y1 - y0);
	if(step)
	{
		swapValue(&x0, &y0);
		swapValue(&x1, &y1);
	}
	if (x1<x0)
	{
		swapValue(&x0, &x1);
		swapValue(&y0, &y1);
	}

	float error = 0.0;
	float roundError = (float) abs(y1-y0)/(x1-x0);
	int y = y0;
	int ystep = (y1>y0 ? 1 : -1);

	for (int i = x0; i < x1; i++)
	{
		if (step)
			putPixel(dest, y, i, r, g, b);
		else
			putPixel(dest, i, y, r, g, b);

		error += roundError;
		if (error >= 0.5)
		{
			y+=ystep;
			error -= 1.0;
		}
	}
}

void drawBoldLine(SDL_Surface* dest, int x0, int y0, int x1, int y1, int size, int r, int g, int b)
{
	int shadow = 50;

	size = (size <= 1 ? 1 : size);
	r = (r < shadow ? shadow : r);
	g = (g < shadow ? shadow : g);
	b = (b < shadow ? shadow : b);

	// draw shadow
	for (int i = size/2; i <= size; i++)
	{
		drawLine(dest, x0, y0 - i, x1, y1 - i, r - shadow, g - shadow, b - shadow);
		drawLine(dest, x0, y0 + i, x1, y1 + i, r - shadow, g - shadow, b - shadow);
		drawLine(dest, x0 - i, y0, x1 - i, y1, r - shadow, g - shadow, b - shadow);
		drawLine(dest, x0 + i, y0, x1 + i, y1, r - shadow, g - shadow, b - shadow);
	}

	// draw main line
	for (int i = 0; i <= size / 2; i++)
	{
		drawLine(dest, x0, y0 - i, x1, y1 - i, r, g, b);
		drawLine(dest, x0, y0 + i, x1, y1 + i, r, g, b);
		drawLine(dest, x0 - i, y0, x1 - i, y1, r, g, b);
		drawLine(dest, x0 + i, y0, x1 + i, y1, r, g, b);
	}
}