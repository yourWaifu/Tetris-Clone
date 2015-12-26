#pragma once
#include <SDL/SDL.h>
#include <cmath>
#include "Block.h"
#include "GridClass.h"

//rotation direction
#define counterClockwise -1
#define clockwise 1

enum reason {
	falling,
	moving,
	spawning,
	rotating
};

struct WallKickData
{
	WallKickData(int (&_clockwiseData)[4][5][2], int (&_counterClockwiseData)[4][5][2]);
	WallKickData();
	const static unsigned int states = 4;
	const static unsigned int tests = 5;
	const static unsigned int positions = 2;
	int (*clockwiseData)[states][tests][positions];
	int (*counterClockwiseData)[states][tests][positions];
};

//here is a list of tetrominos I, J, L, O, S, T, Z
class Tetromino
{
public:
	Tetromino(int h, int w, int(&shape)[4][4][4], int _color, WallKickData &_WallKickData);
	Tetromino();
	~Tetromino();

	//places the arrary being pasted into _shape
	//void defineShape(int(&shape)[4][4][4]);
	//this will draw the tetromino
	void draw(SDL_Renderer* renderer);
	void fall(GridClass* grid);
	void move(GridClass* grid, int velocity);
	void rotate(GridClass* grid, int direction);
	bool wallKick(GridClass * grid, int direction);
	void changeFallSpeed(int fallSpeed);
	//this detects if the tetromino is inside one another
	bool detectCollision(GridClass* grid, reason theReason);
	//places the tetromino onto the grid
	void land(GridClass* grid);
	//void changeVelocity(unsigned int index, int value);
	bool haslanded();
	int shapeSize;
	int y = 3;
	int x = 3;
private:
	void resetVelocity();		//velocity is 0
	int _h;
	int _w;
	int gridx;
	int gridy;
	int rotation;
	int velocity[2];
	int (*shape)[4][4][4];
	int color;
	//int blockSize;
	int _fallSpeed;		//changes when to fall
	bool hasLanded = false;
	WallKickData *WallKick_Data;
};
