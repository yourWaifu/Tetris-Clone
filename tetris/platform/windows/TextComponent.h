#pragma once
#include <string>
#include <sys.h>
#ifdef SDL
#include <SDL_ttf\SDL_ttf.h>
#endif // SYS
//#include <windows.h>

class TextComponent
{
public:
	TextComponent(const char *file, int ptsize, SDL_Color color);
	TextComponent();
	~TextComponent();

	void draw(SDL_Renderer* renderer, const char *text, int x, int y);
	void changeFont(const char *file, int ptsize);
	void changeColor(Uint8 r, Uint8 g, Uint8 b);
private:
	
	TTF_Font *textFont;
	SDL_Texture *textTexture;
	SDL_Color textColor;
	SDL_Surface* textSurface;
	//std::string text;
	std::string fontFile;	//this is so we can tell what we have
	int pointSize;
};

