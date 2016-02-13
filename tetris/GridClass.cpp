#include "GridClass.h"



GridClass::GridClass()
{
}


GridClass::~GridClass()
{
	clear();
}

void GridClass::draw(SDL_Renderer* renderer)
{
	int c = 'NaC';
	Block b;
	for (int fh = 0; fh < h; fh++) {
		for (int fw = 0; fw < w; fw++) {
			if (c != landed[fh][fw]) {
				c = landed[fh][fw];
				setDrawColor(renderer, c);
			}
			//if (c != 0) {					//make it so that we don't have to draw every emty space
				b.draw(renderer, fw * 20, fh * 20);
			//}
		}
	}
}

int GridClass::returnBlockColor(int px, int py)
{
	return landed[py][px];
}

void GridClass::placeBlock(int color, int x, int y)
{
	if (color != 0)
		landed[y][x] = color;
}

void GridClass::clear()
{
	for (int fh = 0; fh < h; fh++) {
		for (int fw = 0; fw < w; fw++) {
			landed[fh][fw] = 0;
		}
	}
}

int GridClass::detectFilledLine()
{
	int countOfRemovedLines = 0;
	for (int fh = 0; fh < h; fh++) {
		bool isFilled = true;
		for (int fw = 0; fw < w; fw++)
			if (landed[fh][fw] == 0)
				isFilled = false;
	//if row is filled do whatever is below the line
		if (isFilled) {
			removeLine(fh);
			countOfRemovedLines++;
		}
	}
	return countOfRemovedLines;
}

void GridClass::removeLine(int line)
{
	//overwrites the lines on line and the ones above it with lines that is right above it, and add last line with 0s
	for (int fh = line; -1 < fh; fh--) {
		for (int fw = 0; fw < w; fw++) {
			if (fh == 0) {
				landed[0][fw] = 0;
				break;
			}
			landed[fh][fw] = landed[fh - 1][fw];
		}
	}
}
