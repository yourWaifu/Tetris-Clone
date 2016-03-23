#include "../../GameClass.h"

void startPlaying(SDL_Rect *Size, SDL_Renderer *ren, SDL_Window *window, state* stateOfTheGame);

int main(int argc, char **argv) {

	SDL_Init(SDL_INIT_EVERYTHING);
	TTF_Init();
	
	// Create an application window with the following settings
	gameResolution.change(400, 480);
	SDL_Rect windowSize;
	windowSize.x = 0;
	windowSize.y = 0;
	windowSize.w = gameResolution.w;
	windowSize.h = gameResolution.h;

	SDL_Window *window = SDL_CreateWindow(
		"Tetris Clone made by a bad programmer",                  // window title
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
		startPlaying(&windowSize, renderer, window, &gameState);
	}

	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

void startPlaying(SDL_Rect *Size, SDL_Renderer *ren, SDL_Window *window, state* stateOfTheGame) {
	std::auto_ptr<GameClass> Tetris(new GameClass(Size, ren, stateOfTheGame));
	//SDL_Delay(1000);
}


/*
The carzy to-do list
fix up speed timing code
bug maybe?	the bag doesn't feel like it's working
add speed timings such as internal gravity and delays
add score
add combo multiper
add score level multiplier
maybe add rising garbage

add input component
*/