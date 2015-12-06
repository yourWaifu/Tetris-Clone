#include "TextComponent.h"

TextComponent::TextComponent(const char *file, int ptsize, SDL_Color color)
{
	textFont = TTF_OpenFont(file, ptsize);
	textColor = color;
	fontFile = file;
	ptsize = pointSize;
}

TextComponent::TextComponent() {

}

TextComponent::~TextComponent()
{
	TTF_CloseFont(textFont);
	SDL_DestroyTexture(textTexture);
}

void TextComponent::draw(SDL_Renderer* renderer, const char *text, int x, int y)
{
	if (textFont == NULL)
		return;//OutputDebugString(TTF_GetError());
	SDL_Rect textRect = { x, y };
	TTF_SizeText(textFont, text, &textRect.w, &textRect.h);
	textSurface = TTF_RenderText_Blended(textFont, text, textColor);		//because TTF_RenderText can only be used on SDL_Surface then we have to create the surface first 
	textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);	//then you convert it to a texture
	SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
	SDL_FreeSurface(textSurface);	//removes the surface, so that there isn't lots of surfaces in memory
	SDL_DestroyTexture(textTexture);
}

void TextComponent::changeFont(const char *file, int ptsize)
{
	if (file != NULL)
		fontFile = file;
	if (ptsize != NULL)
		pointSize = ptsize;
	TTF_CloseFont(textFont);
	textFont = TTF_OpenFont(file, ptsize);
}

void TextComponent::changeColor(Uint8 r, Uint8 g, Uint8 b)
{
	textColor.r = r;
	textColor.g = g;
	textColor.b = b;
}