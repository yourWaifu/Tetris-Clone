#include "Block.h"

void setDrawColor(SDL_Renderer* renderer,int c)
{
	Uint8 red = 0;
	Uint8 green = 0;
	Uint8 blue = 0;
	Uint8 a = 0;

	switch (c) {
	//color nothing
	case 0: red = 25;
		green = 25;
		blue = 25;
		break;
		//color: cyan
	case 1: green = 255;
		blue = 255;
		break;
		//color blue
	case 2: blue = 255;
		break;
		//color orange
	case 3: red = 255;
		green = 127;
		break;
		//color yellow
	case 4: red = 255;
		green = 255;
		break;
		//color lime
	case 5: red = 191;
		green = 255;
		break;
		//color purple
	case 6: red = 128;
		blue = 128;
		break;
		//color red
	case 7: red = 255;
		break;
	}

	SDL_SetRenderDrawColor(renderer, red, green, blue, a);
}

void Block::draw(SDL_Renderer* renderer, int x, int y)
{
	BlockRect.x = x;
	BlockRect.y = y - 40; //BlockRect.y = y * 20 * 4  this is to not show the top five blocks so that the blocks spawn at the top
	SDL_RenderFillRect(renderer, &BlockRect);
}

Block::Block()
{
	BlockRect.w = blockSize;
	BlockRect.h = blockSize;
}
