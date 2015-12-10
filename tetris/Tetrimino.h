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
	spawning
};

//here is a list of tetriminos I, J, L, O, S, T, Z
class Tetrimino
{
public:
	Tetrimino(int h, int w, int yAxisStartOffset, int(&shape)[4][4][4]);
	Tetrimino();
	~Tetrimino();

	//places the arrary being pasted into _shape
	void defineShape(int(&shape)[4][4][4]);
	//this will draw the tetrimino
	void draw(SDL_Renderer* renderer);
	void fall(GridClass* grid);
	void move(GridClass* grid);
	void rotate(int direction);
	void changeFallSpeed(int fallSpeed);
	//this detects if the tetrimino is inside one another
	bool detectCollision(GridClass* grid, reason theReason);
	//places the tetrimino onto the grid
	void land(GridClass* grid);
	void changeVelocity(unsigned int index, int value);
	bool haslanded();
	int shapeSize;
	int y = 4;
	int x = 3;
private:
	int _h;
	int _w;
	int gridx;
	int gridy;
	int rotation;
	int velocity[2];
	int _shape[4][4][4];
	//int blockSize;
	int _fallSpeed;		//changes when to fall
	bool hasLanded = false;
};
