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

Block::Block()
{
	BlockRect.w = (int)((blockSize / blockBorder) * gameResolution.resolutionToOldStandardRatios[1]);
	BlockRect.h = BlockRect.w;
	BorderPxSize = (int)((gameResolution.resolutionToOldStandardRatios[1] * blockSize) - BlockRect.w);
}

void Block::updateCoordinates(int x, int y) {
	BlockRect.x = leftSideX + (int)((x * 20) * gameResolution.resolutionToOldStandardRatios[1] + BorderPxSize);
	BlockRect.y = (int)(((y * 20) - 40) * gameResolution.resolutionToOldStandardRatios[1] + BorderPxSize); //BlockRect.y = y * 20 * 4  this is to not show the top five blocks so that the blocks spawn at the top
}

void Block::draw(SDL_Renderer* renderer, int x, int y, bool SrippledAlpha)
{
	if (SrippledAlpha) {
		drawSrippledAlpha(renderer, x, y);
		return;
	}
	updateCoordinates(x, y);
	SDL_RenderFillRect(renderer, &BlockRect);
}

void Block::drawSrippledAlpha(SDL_Renderer* renderer, int x, int y)
{
	updateCoordinates(x, y);
	const Uint32 area = BlockRect.w * BlockRect.h;
	const Uint32 numOfPoints = (Uint32)(area/2 + 1);
	SDL_Point * points = new SDL_Point[numOfPoints];
	int j = 0;
	for (Uint32 i = 0; i < area; i++) {
		const Uint32 fx = i % BlockRect.w;
		const Uint32 fy = (Uint32)(i / BlockRect.w);
		if ((fx + fy) % 2 == 0) {
			points[j].x = BlockRect.x + fx;
			points[j].y = BlockRect.y + fy;
			++j;
		}
	}
	SDL_RenderDrawPoints(renderer, points, j + 1);
	delete points;
}
