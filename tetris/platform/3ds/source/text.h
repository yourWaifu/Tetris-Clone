#pragma once
#include <3ds.h>
#include "sys_3ds.h"

typedef struct SDL_Renderer SDL_Renderer;

class TextComponent
{
public:
	TextComponent();
	~TextComponent();

	void draw(SDL_Renderer* renderer, const char *text, int x, int y);
};