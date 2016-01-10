#include "Block.h"

void setDrawColor(SDL_Renderer* renderer,int c)
{
	SDL_Color color = getDrawColor(c);
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

SDL_Color getDrawColor(int c) {
	SDL_Color color = {0, 0, 0};

	switch (c) {
	//color nothing
	case 0: color.r = 25;
		color.g = 25;
		color.b = 25;
		break;
		//color: cyan
	case 1: color.g = 255;
		color.b = 255;
		break;
		//color blue
	case 2: color.b = 255;
		break;
		//color orange
	case 3: color.r = 255;
		color.g = 127;
		break;
		//color yellow
	case 4: color.r = 255;
		color.g = 255;
		break;
		//color lime
	case 5: color.r = 191;
		color.g = 255;
		break;
		//color purple
	case 6: color.r = 128;
		color.b = 128;
		break;
		//color red
	case 7: color.r = 255;
		break;
	}
	return color;
}

void Block::draw(SDL_Renderer* renderer, int x, int y)
{
	BlockRect.x = x + BorderPxSize;
	BlockRect.y = y - 40 + BorderPxSize; //BlockRect.y = y * 20 * 4  this is to not show the top five blocks so that the blocks spawn at the top
	SDL_RenderFillRect(renderer, &BlockRect);
}

Block::Block()
{
	BlockRect.w = blockSize / blockBorder;
	BlockRect.h = blockSize / blockBorder;
	BorderPxSize = blockSize - BlockRect.w;
}
