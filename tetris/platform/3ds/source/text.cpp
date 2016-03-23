#include "text.h"

TextComponent::TextComponent() {

}

TextComponent::~TextComponent() {

}

void TextComponent::draw(SDL_Renderer* renderer, const char *text, int x, int y) {
	printText(text);
}