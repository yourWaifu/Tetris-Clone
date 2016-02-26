#pragma once
#include "sys_3ds.h"
#include "rect.h"

#define SCREEN_WIDTH 400
#define SCREEN_HIGHET 240
#define NUM_OF_BYTES 3

typedef struct SDL_Renderer {
	u8* buffer;
	u8 color[NUM_OF_BYTES];
} SDL_Renderer;

SDL_Renderer* SDL_CreateRenderer();
extern int SDL_SetRenderDrawColor(SDL_Renderer * renderer,
					Uint8 r, Uint8 g, Uint8 b,
					Uint8 a);
extern void SDL_RenderFillRects(SDL_Renderer * renderer,
								const SDL_Rect * rects,
								int count);
extern void SDL_RenderFillRect(SDL_Renderer * renderer,
								const SDL_Rect * rect);
extern void SDL_RenderDrawPoint(SDL_Renderer * renderer,
								int x, int y);
extern void SDL_RenderDrawPoints(SDL_Renderer * renderer,
								const SDL_Point * points,
								int count);
extern void SDL_RenderPresent(SDL_Renderer * renderer);

