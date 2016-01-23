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
	//first, we define all Tetrominoes aka hardcode all Tetrominoes and it's wall kick data and Speed Timings
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
	int normalClockwiseWallKickData[WallKickData::states][WallKickData::tests][WallKickData::positions] = {
		{ { 0, 0 },{ 1, 0 },{ 1,1 },{ 0,-2 },{ 1,-2 } },
		{ { 0, 0 },{ 1, 0 },{ 1,-1 },{ 0,2 },{ 1,2 } },
		{ { 0, 0 },{ -1, 0 },{ -1,1 },{ 0,-2 },{ -1,-2 } },
		{ { 0, 0 },{ -1, 0 },{ -1,-1 },{ 0,2 },{ -1,2 } }
	};
	int normalCounterClockwiseData[WallKickData::states][WallKickData::tests][WallKickData::positions] = {
		{ { 0, 0 },{ -1, 0 },{ -1,1 },{ 0,-2 },{ -1,-2 } },
		{ { 0, 0 },{ 1, 0 },{ 1,-1 },{ 0,2 },{ 1,2 } },
		{ { 0, 0 },{ 1, 0 },{ 1,1 },{ 0,-2 },{ 1,-2 } },
		{ { 0, 0 },{ -1, 0 },{ -1,-1 },{ 0,2 },{ -1,2 } }
	};
	WallKickData NormalWallKickData(normalClockwiseWallKickData, normalCounterClockwiseData);

	int shapeIClockwiseWallKickData[WallKickData::states][WallKickData::tests][WallKickData::positions] = {
		{ { 0, 0 },{ -2, 0 },{ 1, 0 },{ -2,-1 },{ 1,2 } },
		{ { 0, 0 },{ -2, 0 },{ 1, 0 },{ 1,-2 },{ -2,1 } },
		{ { 0, 0 },{ -1, 0 },{ 2, 0 },{ -1,-2 },{ 2,1 } },
		{ { 0, 0 },{ 2, 0 },{ -1, 0 },{ 2,-1 },{ -1,1 } }
	};
	int shapeICounterClockwiseWallKickData[WallKickData::states][WallKickData::tests][WallKickData::positions] = {
		{ { 0, 0 },{ 2, 0 },{ -1, 0 },{ 2,-1 },{ -1,2 } },
		{ { 0, 0 },{ -2, 0 },{ 1, 0 },{ -2,-1 },{ 1,1 } },
		{ { 0, 0 },{ 1, 0 },{ -2, 0 },{ 1,-2 },{ -2,1 } },
		{ { 0, 0 },{ 2, 0 },{ -1, 0 },{ -1,-2 },{ 2,1 } }
	};
	WallKickData shapeIWallKickData(shapeIClockwiseWallKickData, shapeICounterClockwiseWallKickData);

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
	Tetromino I(1, 4, shapeI, 1, shapeIWallKickData);
	
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
	allTetrominoes = { &I, &J, &L, &O, &S, &T, &Z };

	//***define time variables.***
	previousFrameTime = 0;
	currentFrameTime = SDL_GetPerformanceCounter();
	timerFrequency = SDL_GetPerformanceFrequency();
	msTime = SDL_GetTicks();
	timeForNextFall = currentFrameTime + timerFrequency;

	int internalGravity[InternalGravity::numOfLevels][InternalGravity::numOfTypesPlusLevel] = {
		{0,		1024},
		{30,	1536},
		{35,	2048},
		{40,	2560},
		{50,	3072},
		{60,	4096},
		{70,	8192},
		{80,	12288},
		{90,	16384},
		{100,	20480},
		{120,	24576},
		{140,	28672},
		{160,	32768},
		{170,	36864},
		{200,	1024},
		{220,	8192},
		{230,	16384},
		{233,	24576},
		{236,	32768},
		{239,	40960},
		{243,	49152},
		{247,	57344},
		{251,	65536},
		{300,	131072},
		{330,	196608},
		{360,	262144},
		{400,	327680},
		{420,	262144},
		{450,	196608},
		{500,	1310720}
	};
	InternalGravity_Data.data = &internalGravity;
	int Delays[Delays::numOfLevels][Delays::numOfTypesPlusLevel] = {
		{0,		14,	30},
		{500,	8,	30},
		{600,	8,	30},
		{700,	8,	30},
		{800,	8,	30},
		{900,	6,	17},
		{1000,	6,	17},
		{1100,	6,	15},
		{1200,	6,	15}
	};
	Delays_Data.data = &Delays;

	//***random***
	srand((unsigned int)time(NULL) + (unsigned int)SDL_GetPerformanceCounter());
	seed_v = rand() + (uint32_t)time(NULL);
	mt.seed(seed_v);
	//***we have to state that the game is now running and that it's the first level, clear everything else***
	level = -3;
	bag[0] = 6; bag[1] = 4; bag[2] = 6; bag[3] = 4; 
	grid.clear();
	*gameState = in_game;
	holdingTetrominoIndex = 'n/a';
	canHoldTetromino = true;
	for (int i = 0; i < sizeOfRandomTetrominoesIndex; i++) {		//makes everything in the randomTetrominoesIndex array = n/a
		randomTetrominoesIndex[i] = 'n/a';
	}
	canShowGhostPiece = true;

	//***UI***
	InGameUI.changeFont("fonts/calibri.ttf", 24);
	InGameUI.changeColor(255, 255, 255);

	//***loop time***
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
	gameLoopdt = gameLoopdt / timerFrequency;
	/*//start of debugcode
	std::string dtstring = std::to_string(gameLoopdt) + '\n';
	OutputDebugString(dtstring.c_str());
	//end of debi*/
	const float minFrametime = timerFrequency / maxfps;
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
	if (canShowGhostPiece) HardDropHint.draw(FallingTetrimno, renderer);
	FallingTetrimno.draw(renderer);
	HoldingTetrimno.draw(renderer);
	//draw next Tetrimno
	for (int i = 0; i < sizeOfRandomTetrominoesIndex - 1; i++) {
		NextTetrimno = *allTetrominoes[randomTetrominoesIndex[i+1]];
		NextTetrimno.x = 4 * i + 3;
		NextTetrimno.y = 1;
		NextTetrimno.draw(renderer);
	}
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
					potentialVelocity[0] = (states[SDL_GetScancodeFromKey(moveRight)] || states[SDL_GetScancodeFromKey(moveRight2)]) - (states[SDL_GetScancodeFromKey(moveLeft)] || states[SDL_GetScancodeFromKey(moveLeft2)]);
					timeForNextMove = msTime;
					DAS = 0;
				}
				if (states[SDL_GetScancodeFromKey(holdTetromino)]) hold();
				if (event.key.keysym.sym == hardDrop) FallingTetrimno.hardDrop(&grid, &HardDropHint);
				if (event.key.keysym.sym == rotateClockwise) FallingTetrimno.rotate(&grid, clockwise);
				if (event.key.keysym.sym == rotateCounterClockwise) FallingTetrimno.rotate(&grid, counterClockwise);
				break;
			case SDL_KEYUP:
				if ((!states[SDL_GetScancodeFromKey(moveRight)] || !states[SDL_GetScancodeFromKey(moveRight2)]) || (!states[SDL_GetScancodeFromKey(moveLeft)] || !states[SDL_GetScancodeFromKey(moveLeft2)])) {
					potentialVelocity[0] = (states[SDL_GetScancodeFromKey(moveRight)] || states[SDL_GetScancodeFromKey(moveRight2)]) - (states[SDL_GetScancodeFromKey(moveLeft)] || states[SDL_GetScancodeFromKey(moveLeft2)]);
					timeForNextMove = msTime;
				}
				break;
		}
	}
}

void GameClass::updateGame()
{
	if (FallingTetrimno.returnIsLocked() || (randomTetrominoesIndex[0] == 'n/a' && randomTetrominoesIndex[1] != 'n/a')) {
		for (int i = 0; i < sizeOfRandomTetrominoesIndex; i++) {
			randomTetrominoesIndex[i] = randomTetrominoesIndex[i + 1];
		}
		randomTetrominoesIndex[3] = 'n/a';
		spawnNewFallingTetromino();
	}
	for (int l = 0; l < sizeOfRandomTetrominoesIndex; l++) {
		// randomness in tgm is crazy, This is the outdated one, becuase I don't understand how the newer one works
		if (randomTetrominoesIndex[l] == 'n/a') {
			level++;
			std::uniform_int_distribution<int> int_dist6(0, 6);
			for (int i = 0; i < 6; i++) {
				randomTetrominoesIndex[l] = int_dist6(mt);		//gen random number from 0 to 6
				bool isInBag = false;
				for (int j = 0; j < 4; j++) {				//checks if it's in the bag
					if (bag[j] == randomTetrominoesIndex[l]) {
						isInBag = true;
						break;
					}
				}
				if (level == -2 && (randomTetrominoesIndex[l] == 3 || (i == 5 && isInBag == true))) {	//makes sure there is a block for first turn and that it isn't a O block
					i--;
				}
				else if (!isInBag) {		//if it's not in the bag, put it in the bag and take out the last one
					for (int j = 3; j > -1; j--) {
						if (j == 0) bag[0] = randomTetrominoesIndex[l];
						else bag[j] = bag[j - 1];
					}
					break;
				}
			}
			/*//debug help
			std::string randomTetrominoesIndexString = std::to_string(randomTetrominoesIndex);
			OutputDebugString(randomTetrominoesIndexString.c_str());
			//end*/
			if (l == 0) {
				spawnNewFallingTetromino();
			}
		}							//end of gettting random tetriminos
	}
	while (timeForNextFall <= currentTime && !FallingTetrimno.returnHasLanded()) {		//when to fall
		FallingTetrimno.fall(&grid);
		if (FallingTetrimno.returnHasLanded())
			timeToLock = msTime + Delays_Data.getRoundedDataInUnitOfTimeFromLevel(1000, level, Delays::Lock);
		timeForNextFall += InternalGravity_Data.getRoundedDataInUnitOfTimeFromLevel(timerFrequency, level);
	}
	if (FallingTetrimno.returnHasLanded()) {
		FallingTetrimno.land(&grid, timeToLock, msTime);
		if (FallingTetrimno.returnIsLocked()) {		//remove filled lines, and increment score and level
													//TO DO add score variable
			int numberOfFilledLines = grid.detectFilledLine();
			if (0 < numberOfFilledLines) {
				level += (int)(float)((double)numberOfFilledLines * 1.5);
			}
			canHoldTetromino = true;
		}
	}
	while (timeForNextMove <= msTime && potentialVelocity[0] != 0) {
		FallingTetrimno.move(&grid, potentialVelocity[0]);
		if (!DAS) {
			timeForNextMove += Delays_Data.getRoundedDataInUnitOfTimeFromLevel(1000, level, Delays::DAS);
			++DAS;
		} else
			timeForNextMove += 16;
	}
	if (100 < level) canShowGhostPiece = false;
	HardDropHint.update(&grid, FallingTetrimno);
}

void GameClass::hold()
{
	if (canHoldTetromino == false) return;
	if (randomTetrominoesIndex[0] == 'n/a') return;
	int t = randomTetrominoesIndex[0];
	randomTetrominoesIndex[0] = holdingTetrominoIndex;
	holdingTetrominoIndex = t;
	HoldingTetrimno = *allTetrominoes[holdingTetrominoIndex];
	HoldingTetrimno.x = 0;
	HoldingTetrimno.y = 1;
	if (randomTetrominoesIndex[0] != 'n/a')
		FallingTetrimno = *allTetrominoes[randomTetrominoesIndex[0]];
	canHoldTetromino = false;
}

void GameClass::spawnNewFallingTetromino()
{
	FallingTetrimno = *allTetrominoes[randomTetrominoesIndex[0]];
	if (FallingTetrimno.detectCollision(&grid, spawning)) {
		*gameState = lost;
	}
	timeForNextFall = currentFrameTime + InternalGravity_Data.getRoundedDataInUnitOfTimeFromLevel(timerFrequency, level);	//this is used to synchronize the timings
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
	randomTetrominoesIndex = 'n/a';
	timeForNextFall = msTime + 1000;
}
*/
