#pragma once
//#include <iostream>
#include <sys.h>
#ifdef SDL
#include "platform/windows/TextComponent.h"
#endif
#include <array>
#include <sstream>
#include <string>
//#include <windows.h>	//this is for debugging only. I think
/*here is the debug code I like to use
std::string dbstring = std::to_string(number) + '\n';
OutputDebugString(dbstring.c_str());
*/
#include <random>
#include <chrono>
#include "SpeedTimingData.h"
#include "Tetromino.h"
#include "common.h"
#include "menus.h"
#include "InputComponent.h"
#include "config_file.h"

const SDL_Color white = { 255, 255, 255 };
extern bool canShowGhostPiece;

enum state {
	starting,
	quit,
	lost,
	in_game,
	paused
};

class GameClass
{
public:
	GameClass(SDL_Rect *Size, SDL_Renderer *ren, state* stateOfTheGame);
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
	void pause(const Uint8* states);
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
	SDL_Renderer *renderer;
	SDL_Event _event; //I have a feeling that this shouldn't be here
	//SDL_Window *window;
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
	//random
	std::mt19937 mt;
	uint32_t seed_v;
	//input
	//game
	InputAction moveLeft;
	InputAction moveRight;
	InputAction rotateClockwise;
	InputAction rotateCounterClockwise;
	InputAction holdTetromino;
	InputAction hardDrop;

	InputAction openMenu;
	InputAction menuMoveUp;
	InputAction menuMoveDown;
	InputAction menuSelect;
	InputAction menuUpOneLevel;
	//SDL_Keycode moveLeft = SDLK_a;
	//SDL_Keycode moveRight = SDLK_d;
	//SDL_Keycode moveLeft2 = SDLK_LEFT;
	//SDL_Keycode moveRight2 = SDLK_RIGHT;
	//SDL_Keycode rotateClockwise = SDLK_k;
	//SDL_Keycode rotateCounterClockwise = SDLK_j;
	//SDL_Keycode holdTetromino = SDLK_u;
	//SDL_Keycode hardDrop = SDLK_w;
	//SDL_Keycode hardDrop2 = SDLK_UP;
	//menus

	//SDL_Keycode menuMoveUp = SDLK_w;
	//SDL_Keycode menuMoveDown = SDLK_s;
	//SDL_Keycode menuSelect = SDLK_j;
	//SDL_Keycode menuUpOneLevel = SDLK_k;
	//UI
	TextComponent InGameUI;
};
