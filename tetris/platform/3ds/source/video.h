#pragma once
#include "sys_3ds.h"

typedef struct SDL_Color
{
	Uint8 r;
	Uint8 g;
	Uint8 b;
	Uint8 a;
} SDL_Color;
#define SDL_Colour SDL_Color

void printText(const char text[]);