#include "GameClass.h"

GameClass::GameClass(SDL_Rect *Size, SDL_Window *win, SDL_Renderer *ren, state* stateOfTheGame)
{
	windowSize = Size;
	window = win;
	renderer = ren;
	gameState = stateOfTheGame;
	//run start game function. what do you think it does?
	startGame();
}


GameClass::~GameClass()
{
	
}

void GameClass::startGame()
{
	//first, we define all Tetrominos aka hardcode all Tetrominos and it's wall kick data
	/*
	different numbers mean different color
	0 = n/a empty space
	1 = cyan
	2 = blue
	3 = orange
	4 = yellow
	5 = lime
	6 = purple
	7 = red
	wall kicks are when the player attempts to rotate a tetromino, but the position 
	*/
	//wall kick data
	int normalClockwiseWallKickData[4][5][2] = { 
		{ { 0, 0 },{ 1, 0 },{ 1,-1 },{ 0,2 },{ 1,2 } },
		{ { 0, 0 },{ 1, 0 },{ 1,1 },{ 0,-2 },{ 1,-2 } },
		{ { 0, 0 },{ -1, 0 },{ -1,-1 },{ 0,2 },{ -1,2 } },
		{ { 0, 0 },{ -1, 0 },{ -1,1 },{ 0,-2 },{ -1,-2 } }
	};
	int normalCounterClockwiseData[4][5][2] = {
		{ { 0, 0 },{ -1, 0 },{ -1,-1 },{ 0,2 },{ -1,2 } },
		{ { 0, 0 },{ 1, 0 },{ 1,1 },{ 0,-2 },{ 1,-2 } },
		{ { 0, 0 },{ 1, 0 },{ 1,-1 },{ 0,2 },{ 1,2 } },
		{ { 0, 0 },{ -1, 0 },{ -1,1 },{ 0,-2 },{ -1,-2 } }
	};
	WallKickData NormalWallKickData(normalClockwiseWallKickData, normalCounterClockwiseData);

	int shapeI[4][4][4] = {	{	{ 0, 0, 0, 0 }, 
								{ 1, 1, 1, 1 },
								{ 0, 0, 0, 0 },
								{ 0, 0, 0, 0 }	},
								
							{	{ 0, 0, 1, 0 },
								{ 0, 0, 1, 0 },
								{ 0, 0, 1, 0 },
								{ 0, 0, 1, 0 }	},

							{	{ 0, 0, 0, 0 },
								{ 0, 0, 0, 0 },
								{ 1, 1, 1, 1 },
								{ 0, 0, 0, 0 }	},
	
							{	{ 0, 1, 0, 0 },
								{ 0, 1, 0, 0 },
								{ 0, 1, 0, 0 },
								{ 0, 1, 0, 0 }	}	};
	//piece: I, color: cyan. It's a line//gets it's own wallkickdata
	Tetromino I(1, 4, shapeI, 1, NormalWallKickData);
	
	int shapeJ[4][4][4] = {	{	{ 0, 0, 0 },
								{ 2, 2, 2 },
								{ 0, 0, 2 }	},

							{	{ 0, 2, 0 },
								{ 0, 2, 0 },
								{ 2, 2, 0 }	},
	
							{	{ 2, 0, 0 },
								{ 2, 2, 2 },
								{ 0, 0, 0 } },
	
							{	{ 0, 2, 2 },
								{ 0, 2, 0 },
								{ 0, 2, 0 }	}	};
	//piece J, color blue. it's a reverse L
	Tetromino J(2, 3, shapeJ, 2, NormalWallKickData);

	int shapeL[4][4][4] = { {	{ 0, 0, 0 },
								{ 3, 3, 3 },
								{ 3, 0, 0 }	},

							{	{ 3, 3, 0 },
								{ 0, 3, 0 },
								{ 0, 3, 0 }	},
	
							{	{ 0, 0, 3 },
								{ 3, 3, 3 },
								{ 0, 0, 0 } },
	
							{	{ 0, 3, 0 },
								{ 0, 3, 0 },
								{ 0, 3, 3 }	}	};
	//piece L, color orange. it's a L
	Tetromino L(2, 3, shapeL, 3, NormalWallKickData);

	int shapeO[4][4][4] = { {	{ 0, 0, 0 },
								{ 0, 4, 4 },
								{ 0, 4, 4 } },
							{	{ 0, 0, 0 },
								{ 0, 4, 4 },
								{ 0, 4, 4 } },
							{	{ 0, 0, 0 },
								{ 0, 4, 4 },
								{ 0, 4, 4 } },
							{	{ 0, 0, 0 },
								{ 0, 4, 4 },
								{ 0, 4, 4 } }, };
	//piece O, color yellow. it's a square of blocks
	Tetromino O(3, 3, shapeO, 4, NormalWallKickData);		//having the O shape as 3 by 3 instead of 2 by 2 fixs a few bugs

	int shapeS[4][4][4] = { {	{ 0, 0, 0 },
								{ 0, 5, 5 },
								{ 5, 5, 0 }	},
							
							{	{ 5, 0, 0 },
								{ 5, 5, 0 },
								{ 0, 5, 0 } },
							
							{	{ 0, 5, 5 },
								{ 5, 5, 0 },
								{ 0, 0, 0 } },
							
							{	{ 0, 5, 0 },
								{ 0, 5, 5 },
								{ 0, 0, 5 }	}	};
	//piece S, color lime. FUCK YOU squiggly line
	Tetromino S(2, 3, shapeS, 5, NormalWallKickData);

	int shapeT[4][4][4] = { {	{ 0, 0, 0 },
								{ 6, 6, 6 },
								{ 0, 6, 0 }	},
								
							{	{ 0, 6, 0 },
								{ 6, 6, 0 },
								{ 0, 6, 0 } },
								
							{	{ 0, 6, 0 },
								{ 6, 6, 6 },
								{ 0, 0, 0 } },

							{	{ 0, 6, 0 },
								{ 0, 6, 6 },
								{ 0, 6, 0 } }	};
	//piece T, color purple. It's like a short t
	Tetromino T(2, 3, shapeT, 6, NormalWallKickData);

	int shapeZ[4][4][4] = { {	{ 0, 0, 0 },
								{ 7, 7, 0 },
								{ 0, 7, 7 } },

							{	{ 0, 7, 0 },
								{ 7, 7, 0 },
								{ 7, 0, 0 } },
	
							{	{ 7, 7, 0 },
								{ 0, 7, 7 },
								{ 0, 0, 0 } },

							{	{ 0, 0, 7 },
								{ 0, 7, 7 },
								{ 0, 7, 0 } }, };
	//piece Z, color red. you're just as bad as S. YOU TOO CAN GO FUCK YOUSELF reverse squiggly line
	Tetromino Z(2, 3, shapeZ, 7, NormalWallKickData);

	//now we put them into an array of pointers
	allTetrominos = { &I, &J, &L, &O, &S, &T, &Z };

	//define time variables.
	previousFrameTime = 0;
	currentFrameTime = SDL_GetPerformanceCounter();
	msTime = SDL_GetTicks();

	//random
	srand((unsigned int)time(NULL) + (unsigned int)SDL_GetPerformanceCounter());
	seed_v = rand() + (uint32_t)time(NULL);
	mt.seed(seed_v);
	//we have to state that the game is now running and that it's the first level, clear everything else
	level = 0;
	bag[0] = 6; bag[1] = 4; bag[2] = 6; bag[3] = 4; 
	grid.clear();
	*gameState = in_game;
	holdingTetrominoIndex = 'n/a';
	canHoldTetromino = true;
	randomTetrominosIndex = 'n/a';
	timeForNextFall = msTime + 1000;

	//UI
	InGameUI.changeFont("fonts/calibri.ttf", 24);
	InGameUI.changeColor(255, 255, 255);

	//loop time
	while (*gameState != lost && *gameState != quit) {
		gameLoop();
	}
	//quit time!!!!1!!11!11111
}

void GameClass::gameLoop()
{
	//first thing in the loop is to update dt
	previousFrameTime = currentFrameTime;
	currentFrameTime = SDL_GetPerformanceCounter();
	//debug code starts here
	double gameLoopdt = (double)currentFrameTime - previousFrameTime;	//loss of data, but I don't know how to fix
	gameLoopdt = gameLoopdt / SDL_GetPerformanceFrequency();
	/*//start of debugcode
	std::string dtstring = std::to_string(gameLoopdt) + '\n';
	OutputDebugString(dtstring.c_str());
	//end of debi*/
	const float minFrametime = SDL_GetPerformanceFrequency() / maxfps;
	currentTime = SDL_GetPerformanceCounter();
	//remember to take a look at http://gameprogrammingpatterns.com/game-loop.html
	while ((currentTime - currentFrameTime) < minFrametime) {
		msTime = SDL_GetTicks();
		processInput();		//note that process input is also used for updating the game
		updateGame();
		currentTime = SDL_GetPerformanceCounter();
	}
	gameDraw();
}

void GameClass::gameDraw()
{
	//draw black all over the screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderFillRect(renderer, windowSize);
	//draw grid
	grid.draw(renderer);
	//draw tetrimino
	FallingTetrimno.draw(renderer);
	HoldingTetrimno.draw(renderer);
	//render level text. you should put this into it's own function
	std::string InGameUIText = "Level " + std::to_string(level);
	const char *InGameUITextChar = InGameUIText.c_str();
	InGameUI.draw(renderer, InGameUITextChar, 200, 400);
	//??????I think this is where it renders the stuff
	SDL_RenderPresent(renderer);
}

void GameClass::processInput()
{
	while (SDL_PollEvent(&event)) {
		const Uint8* states = SDL_GetKeyboardState(NULL);
		switch (event.type) {
			case SDL_QUIT:
				*gameState = quit;
				break;
			case SDL_KEYDOWN:
				//TO_DO MAKE THIS CLEANER
				if ((states[SDL_GetScancodeFromKey(moveRight)] || states[SDL_GetScancodeFromKey(moveRight2)]) || (states[SDL_GetScancodeFromKey(moveLeft)] || states[SDL_GetScancodeFromKey(moveLeft2)])) {
					potentialVelocity = (states[SDL_GetScancodeFromKey(moveRight)] || states[SDL_GetScancodeFromKey(moveRight2)]) - (states[SDL_GetScancodeFromKey(moveLeft)] || states[SDL_GetScancodeFromKey(moveLeft2)]);
					timeForNextMove = msTime;
				}
				if (states[SDL_GetScancodeFromKey(holdTetromino)])
					hold();
				if (event.key.keysym.sym == rotateClockwise)
					FallingTetrimno.rotate(&grid, clockwise);
				if (event.key.keysym.sym == rotateCounterClockwise)
					FallingTetrimno.rotate(&grid, counterClockwise);
				break;
			case SDL_KEYUP:
				if ((!states[SDL_GetScancodeFromKey(moveRight)] || !states[SDL_GetScancodeFromKey(moveRight2)]) || (!states[SDL_GetScancodeFromKey(moveLeft)] || !states[SDL_GetScancodeFromKey(moveLeft2)])) {
					potentialVelocity = (states[SDL_GetScancodeFromKey(moveRight)] || states[SDL_GetScancodeFromKey(moveRight2)]) - (states[SDL_GetScancodeFromKey(moveLeft)] || states[SDL_GetScancodeFromKey(moveLeft2)]);
					timeForNextMove = msTime;
				}
				break;
		}
	}
}

void GameClass::updateGame()
{	
	// randomness in tgm is crazy, This is the outdated one, becuase I don't understand how the newer one works
	if (randomTetrominosIndex == 'n/a' || FallingTetrimno.haslanded()) {
		level++;
		std::uniform_int_distribution<int> int_dist6(0, 6);
		for (int i = 0; i < 6; i++) {
			randomTetrominosIndex = int_dist6(mt);		//gen random number from 0 to 6
			bool isInBag = false;
			for (int j = 0; j < 4; j++) {				//checks if it's in the bag
				if (bag[j] == randomTetrominosIndex) {
					isInBag = true;
					break;
				}
			}
			if (level == 1 && (randomTetrominosIndex == 3 || (i == 5 && isInBag == true))) {	//makes sure there is a block for first turn and that it isn't a O block
				i--;
			}
			else if (!isInBag) {		//if it's not in the bag, put it in the bag and take out the last one
				for (int j = 3; j > -1; j--) {
					if (j == 0) bag[0] = randomTetrominosIndex;
					else bag[j] = bag[j - 1];
				}
				break;
			}
		}
		/*//debug help
		std::string randomTetrominosIndexString = std::to_string(randomTetrominosIndex);
		OutputDebugString(randomTetrominosIndexString.c_str());
		//end*/
		FallingTetrimno = *allTetrominos[randomTetrominosIndex];		//make a new random falling tetrimino
		if (FallingTetrimno.detectCollision(&grid, spawning)) {
			*gameState = lost;
		}
	}							//end of gettting random tetriminos
	if (timeForNextFall <= msTime) {		//when to fall
		FallingTetrimno.fall(&grid);
		timeForNextFall = msTime + 200;	//r3emembew to change this valve
		if (FallingTetrimno.haslanded() == true) {	//remove filled lines, and increment score and level
													//TO DO add score variable
			int numberOfFilledLines = grid.detectFilledLine();
			if (0 < numberOfFilledLines) {
				level += (int)(float)((double)numberOfFilledLines * 1.5);
			}
			canHoldTetromino = true;
		}
	}
	if (timeForNextMove <= msTime) { 
		FallingTetrimno.move(&grid, potentialVelocity);
		timeForNextMove = msTime + 200;
	}
}

void GameClass::hold()
{
	if (canHoldTetromino == false)
		return;
	if (randomTetrominosIndex == 'n/a')
		return;
	int t = randomTetrominosIndex;
	randomTetrominosIndex = holdingTetrominoIndex;
	holdingTetrominoIndex = t;
	HoldingTetrimno = *allTetrominos[holdingTetrominoIndex];
	HoldingTetrimno.x = 0;
	HoldingTetrimno.y = 1;
	if (randomTetrominosIndex != 'n/a')
		FallingTetrimno = *allTetrominos[randomTetrominosIndex];
	canHoldTetromino = false;
}

/* this was for debugging a bug where losing made the game literally unplayable
void GameClass::lose()
{
	//to do add a menu to continue or not
	*gameState = lost;
	//random
	srand((unsigned int)time(NULL) + (unsigned int)SDL_GetPerformanceCounter());
	seed_v = rand() + (uint32_t)time(NULL);
	mt.seed(seed_v);
	//we have to state that the game is now running
	level = 0;
	bag[0] = 6; bag[1] = 4; bag[0] = 6; bag[0] = 4;
	grid.clear();
	*gameState = in_game;
	randomTetrominosIndex = 'n/a';
	timeForNextFall = msTime + 1000;
}
*/