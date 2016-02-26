#pragma once
#include <sys.h>
#include "common.h"
/*
different numbers mean different color
0 = n/a empty space
1 = cyan
2 = blue
3 = orange
4 = yellow
5 = lime
6 = purple
7 = red
*/
void setDrawColor(SDL_Renderer* renderer, int c);
SDL_Color getDrawColor(int c);
//this only sets colors. I should put this somewhere else, but I don't know where


struct Block{
	Block();
	void draw(SDL_Renderer* renderer, int x, int y, bool SrippledAlpha = false);
	void drawSrippledAlpha(SDL_Renderer* renderer, int x, int y);
private:
	void updateCoordinates(int x, int y);
	SDL_Rect BlockRect;
	const int blockSize = 20;
	const float blockBorder = 1.1f;
	int BorderPxSize;	//size of the border in pixals
};