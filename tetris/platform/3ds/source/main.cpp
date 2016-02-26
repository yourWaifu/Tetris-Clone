#include <3ds.h>
#include <memory> 
#include "sys_3ds.h"
#include "../../../GameClass.h"

void startPlaying(SDL_Rect *Size, SDL_Renderer *ren, state* gameState);

int main(int argc, char **argv) {
	gfxInitDefault();
	PrintConsole bottomScreen;//In this example we need one PrintConsole for each screen
	consoleInit(GFX_BOTTOM, &bottomScreen);
	gfxSetDoubleBuffering(GFX_TOP, false);
	consoleSelect(&bottomScreen);
	gameResolution.change(400, 240);
	SDL_Rect windowSize;
	windowSize.x = 0;
	windowSize.y = 0;
	windowSize.w = gameResolution.w;
	windowSize.h = gameResolution.h;
	SDL_Renderer renderer;
	renderer.buffer = (u8*)(malloc(SCREEN_WIDTH * SCREEN_HIGHET * 3));
	renderer.color[0] = 0;
	renderer.color[1] = 0;
	while (((&renderer == NULL) == true)) {
		printText("error no renderer");
	}
	SDL_keyboard.didInit = false;
	SDL_keyboard.init();
	//Game start goes here
	state gameState = starting;
	while (gameState == lost || gameState == starting) {
		gameState = starting;
		startPlaying(&windowSize, &renderer, &gameState);
	}
	free(renderer.buffer);
	gfxExit();
	return 0;
}

void startPlaying(SDL_Rect *Size, SDL_Renderer *ren, state* stateOfTheGame) {
	std::unique_ptr<GameClass> Tetris(new GameClass(Size, ren, stateOfTheGame));	//we are using unique_ptr instead of auto_ptr becuase it makes the complier happy
}