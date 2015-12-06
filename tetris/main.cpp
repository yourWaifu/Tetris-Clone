#include "GameClass.h"

void startPlaying(SDL_Rect *Size, SDL_Window *win, SDL_Renderer *ren, state* gameState);

int main(int argc, char **argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	// Create an application window with the following settings
	SDL_Rect windowSize;
	windowSize.x = 0;
	windowSize.y = 0;
	windowSize.w = 640;
	windowSize.h = 480;

	SDL_Window *window = SDL_CreateWindow(
		"Tetris Clone made by a bad programmer test",                  // window title
		SDL_WINDOWPOS_UNDEFINED,           // initial x position
		SDL_WINDOWPOS_UNDEFINED,           // initial y position
		windowSize.w,                               // width, in pixels
		windowSize.h,                               // height, in pixels
		SDL_WINDOW_OPENGL             // flags - see below
		);

	SDL_Renderer *renderer = SDL_CreateRenderer(
		window,
		-1,
		SDL_RENDERER_ACCELERATED
		);

	// Check that the window was successfully made
	if (window == NULL) {
		// In the event that the window could not be made...
		printf("Could not create window: %s\n", SDL_GetError());
		return 1;
	}

	/*TTF_Font *calibri;
	calibri = TTF_OpenFont("fonts\calibri.ttf", 20);
	TTF_CloseFont(calibri);*/

	//Game start goes here
	state gameState = starting;
	while (gameState == lost || gameState == NULL) {
		gameState = starting;
		startPlaying(&windowSize, window, renderer, &gameState);
	}

	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

void startPlaying(SDL_Rect *Size, SDL_Window *win, SDL_Renderer *ren, state* stateOfTheGame) {
	std::auto_ptr<GameClass> Tetris(new GameClass(Size, win, ren, stateOfTheGame));
	//SDL_Delay(1000);
}


/*

The carzy to-do list
add rotation
add speed timings such as internal gravity and delays
add score
add combo multiper
add score level multiplier
maybe add rising garbage

add input component
add text component
*/