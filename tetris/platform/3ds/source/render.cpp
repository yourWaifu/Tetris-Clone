#include "render.h"

SDL_Renderer* SDL_CreateRenderer()
{
	SDL_Renderer renderer;
	renderer.buffer = (u8*)(malloc(SCREEN_WIDTH * SCREEN_HIGHET * 2))/*gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL)*/;
	return &renderer;
}

int SDL_SetRenderDrawColor(SDL_Renderer * renderer, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	/*const float ratio = 0.12156862745098039215686;	// 31/255
	Uint8 Green = ((Uint8)(float)g * ratio);
	renderer->color[0] = ((Uint8)((float)b * ratio)) | Green << 5;
	renderer->color[1] = ((Uint8)((float)r * ratio) << 3) | Green >> 2;*/
	renderer->color[0] = b;
	renderer->color[1] = g;
	renderer->color[2] = r;
	return 0;
}

void SDL_RenderFillRects(SDL_Renderer * renderer, const SDL_Rect * rects, int count)
{
	for (int i = 0; i < count; i++) {
		//error check
		SDL_Rect currentRect = rects[i];
		if (currentRect.x < 0)
			currentRect.x = 0;
		if (currentRect.y < 0)
			currentRect.y = 0;
		if (SCREEN_WIDTH < (currentRect.x + currentRect.w))
			currentRect.w = SCREEN_WIDTH - currentRect.x;
		if (SCREEN_HIGHET < (currentRect.y + currentRect.h))
			currentRect.h = SCREEN_HIGHET - currentRect.y;
		//draw
		for (int xi = currentRect.x; xi < currentRect.x + currentRect.w; xi++)
			for (int yi = currentRect.y; yi < currentRect.y + currentRect.h; yi++) {
				//if (xi < 0 || SCREEN_WIDTH < xi || yi < 0 || SCREEN_HIGHET < yi) break;
				for (int i = 0; i < NUM_OF_BYTES; i++)
					renderer->buffer[(((xi * SCREEN_HIGHET) + (SCREEN_HIGHET - yi)) * 3) + i] = renderer->color[i];
				//char str[15];
				//sprintf(str, "%d", renderer->buffer[(((xi * SCREEN_HIGHET) + (SCREEN_HIGHET - yi)) * 2) + i]);
				//printText(str);
			}
	}
}

void SDL_RenderFillRect(SDL_Renderer * renderer, const SDL_Rect * rect)
{
	SDL_RenderFillRects(renderer, rect, 1);
}

void SDL_RenderDrawPoint(SDL_Renderer * renderer, int x, int y)
{
	SDL_Point point;
	point.x = x;
	point.y = y;
	SDL_RenderDrawPoints(renderer, &point, 1);
}

void SDL_RenderDrawPoints(SDL_Renderer * renderer, const SDL_Point * points, int count)
{
	for (int i = 0; i < count; i++) {
		if (0 <= points[i].x || points[i].x <= SCREEN_WIDTH || 0 <= points[i].y || SCREEN_HIGHET <= points[i].y) {
			for (int c = 0; c < NUM_OF_BYTES; c++)
				renderer->buffer[(((points[i].x * SCREEN_HIGHET) + (SCREEN_HIGHET - points[i].y)) * NUM_OF_BYTES) + c] = renderer->color[c];
		}
	}
}

void SDL_RenderPresent(SDL_Renderer * renderer)
{
	u8* fb = gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);
	for (int x = 0; x < SCREEN_WIDTH; x++)
		for (int y = 0; y < SCREEN_HIGHET; y++)
			for (int c = 0; c < NUM_OF_BYTES; c++)
				fb[(((x * SCREEN_HIGHET) + (SCREEN_HIGHET - y)) * 3) + c] = renderer->buffer[(((x * SCREEN_HIGHET) + (SCREEN_HIGHET - y)) * 3) + c];
	//gfxFlushBuffers();	//only use for debugging
	gfxSwapBuffers();
	//Wait for VBlank
	gspWaitForVBlank();
}


