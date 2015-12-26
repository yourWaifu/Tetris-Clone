#pragma once
#include <SDL/SDL.h>
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
//this only sets colors. I should put this somewhere else, but I don't know where


struct Block{
	Block();
	void draw(SDL_Renderer* renderer, int x, int y);
private:
	SDL_Rect BlockRect;
	const int blockSize = 20;
	const float blockBorder = 1.1f;
	int BorderPxSize;	//size of the border in pixals
};