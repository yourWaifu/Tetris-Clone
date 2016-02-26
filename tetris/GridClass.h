#pragma once
#include "Block.h"
class GridClass
{
public:
	GridClass();
	~GridClass();
	
	void draw(SDL_Renderer* renderer);
	int returnBlockColor(int px, int py);
	void placeBlock(int color, int x, int y);
	void clear();
	int detectFilledLine();		//check if the rows are filled, and return number of filled lines
	void removeLine(int line);	//remove row
	const static int h = 25;
	const static int w = 10;
private:
	/*Playfield is 10 cells wide and at least 22 cells tall,
	where rows above 20 are hidden or obstructed by the field frame
	TO DO, make this part of the constructor
	*/
	//TO DO later make a function for this
	Uint8 landed[h][w];
};

