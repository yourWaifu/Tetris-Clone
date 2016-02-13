#pragma once
//#include <iostream>
#include <SDL\SDL.h>
#include <array>
//#include <string>
//#include <windows.h>	//this is for debugging only. I think
/*here is the debug code I like to use
std::string dbstring = std::to_string(number) + '\n';
OutputDebugString(dbstring.c_str());
*/
#include <random>
#include <chrono>
#include "SpeedTimingData.h"
#include "TextComponent.h"
#include "Tetromino.h"

const SDL_Color white = { 255, 255, 255 };

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

private:
	void startGame();
	void gameLoop();
	void gameDraw();
	void processInput();
	void updateGame();
	//gameplay functions
	void hold();
	void spawnNewFallingTetromino();
	//void lose();		//only used for debuging for now
	Uint64 previousFrameTime;
	Uint64 currentFrameTime;
	Uint64 currentTime;
	Uint64 timerFrequency;
	Uint32 msTime;
	bool isFramerateLimited = false;
	const float maxfps = 480;
	state* gameState;
	//SDL
	SDL_Rect *windowSize;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event; //I have a feeling that this shouldn't be here
	//gameplay variables
	InternalGravity InternalGravity_Data;
	Delays Delays_Data;
	double timeForNextFall;						//tells us when the block is going to fall in ms
	Uint32 timeForNextMove;
	Uint8 DAS;
	Uint32 timeToLock;
	int potentialVelocity[2];
	int level = 0;
	int holdingTetrominoIndex;
	bool canHoldTetromino;
	const static int sizeOfRandomTetrominoesIndex = 4;
	int randomTetrominoesIndex[sizeOfRandomTetrominoesIndex];
	std::array<Tetromino*, 7> allTetrominoes;	//every tetriminos
	Tetromino FallingTetrimno;
	Tetromino HoldingTetrimno;
	Tetromino NextTetrimno;
	GhostTetromino HardDropHint;
	GridClass grid;								//the grid, what else do you think it is?
	unsigned int seed;
	int bag[4];
	bool canShowGhostPiece;
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
	SDL_Keycode holdTetromino = SDLK_u;
	SDL_Keycode hardDrop = SDLK_w;
	//UI
	TextComponent InGameUI;
};
