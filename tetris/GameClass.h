#pragma once
#include <iostream>
#include <SDL\SDL.h>
#include <array>
#include <string>
//#include <windows.h>	//this is for debugging only. I think
#include <random>
#include <chrono>
#include "TextComponent.h"
#include "Tetrimino.h"

enum state {
	starting,
	quit,
	lost,
	in_game
};

class GameClass
{
public:
	GameClass(SDL_Rect *Size, SDL_Window *win, SDL_Renderer *ren, state* stateOfTheGame);
	~GameClass();

	void startGame();
	void gameLoop();
	void gameDraw();
	void processInput();
	void updateGame();
	//gameplay functions
	//void lose();		//only used for debuging for now

private:
	Uint64 previousFrameTime;
	Uint64 currentFrameTime;
	Uint64 currentTime;
	Uint32 msTime;
	const float maxfps = 480;
	state* gameState;
	//SDL
	SDL_Rect *windowSize;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event; //I have a feeling that this shouldn't be here
	//gameplay variables
	Uint32 timeForNextFall;						//tells us when the block is going to fall in ms
	Uint32 timeForNextMove;
	int level = 0;
	int randomTetriminosIndex;
	std::array<Tetrimino*, 7> allTetriminos;	//every tetriminos
	Tetrimino FallingTetrimno;
	GridClass grid;								//the grid, what else do you think it is?
	unsigned int seed;
	int bag[4] = {6,4,6,4};
	//random
	std::mt19937 mt;
	uint32_t seed_v;
	//input
	SDL_Keycode moveLeft = SDLK_a;
	SDL_Keycode moveRight = SDLK_d;
	SDL_Keycode moveLeft2 = SDLK_LEFT;
	SDL_Keycode moveRight2 = SDLK_RIGHT;
	SDL_Keycode rotateClockwise = SDLK_k;
	SDL_Keycode rotateCounterClockwise = SDLK_j;
	//UI
	const SDL_Color white = { 255, 255, 255 };
	TextComponent InGameUI;
};
