#include "Tetromino.h"


Tetromino::Tetromino(int h, int w, int StartLocationYAxisOffset, int(&shape)[4][4][4])
{
	_h = h;
	_w = w;
	y += StartLocationYAxisOffset;	//this is so that the tetromino starts at the top
	shapeSize = h < w ? w : h;
	rotation = 0;
	velocity[0] = 0; velocity[1] = 0;
	defineShape(shape);
}

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}

void Tetromino::defineShape(int (&shape)[4][4][4])
{
	for (size_t r = 0; r < 4; r++) {
		for (size_t h = 0; h < 4; h++)
			for (size_t w = 0; w < 4; w++) {
				_shape[r][h][w] = shape[r][h][w];
			}
	}
}

void Tetromino::draw(SDL_Renderer* renderer)
{
	//color variable
	int c = 0;
	for (int h = 0; c <= 0 && h < shapeSize; h++) {
		for (int w = 0; w < shapeSize && c <= 0; w++) {
			c += _shape[rotation][h][w];
		}
	}
	
	setDrawColor(renderer, c);
	
	for (int fh = 0; fh < shapeSize; fh++) {
		for (int fw = 0; fw < shapeSize; fw++) {
			if (_shape[rotation][fh][fw] > 0) {
				Block b;
				b.draw(renderer, (x + fw) * 20, (y + fh) * 20);
			}
		}
	}
}

void Tetromino::fall(GridClass* grid)
{
	velocity[1] = 1;
	if (!detectCollision(grid, falling))
		y += velocity[1];
	else
		land(grid);
	velocity[1] = 0;
}

void Tetromino::move(GridClass * grid)
{
	if (!detectCollision(grid, moving))
		x += velocity[0];
}

void Tetromino::rotate(int direction)
{
	//you should check collision before rotating
	//this will break if direction isn't 1 or -1
	if (rotation + direction < 0) {
		rotation = 4 - std::abs(rotation + direction);
	}
	else if (3 < rotation + direction) {
		rotation = (rotation + direction) % 4;
	}
	else {
		rotation += direction;
	}
}

void Tetromino::changeFallSpeed(int fallSpeed)
{
	_fallSpeed = fallSpeed;
}

bool Tetromino::detectCollision(GridClass* grid, reason theReason)
{
	//TO-DO add rotation
	for (int fh = shapeSize - 1; -1 < fh; fh--) {
		for (int fw = 0; fw < shapeSize; fw++) {
			if (_shape[rotation][fh][fw] != 0) {		//checks if there is a block in tetromino at fh and fw
				int blockx = x + fw;
				int blocky = y + fh;
				int newx = blockx + velocity[0];
				int newy = blocky + velocity[1];
				if (theReason == moving && (newx < 0 || newx > 9))
					return true;
				if (theReason == falling && newy > 24)
					return true;
				if (theReason == spawning && grid->returnBlockColor(blockx, blocky) != 0)
					return true;
				if (grid->returnBlockColor(theReason == falling ? blockx : newx, theReason == moving ? blocky : newy) != 0)
					return true;
			}
		}
	}
	return false;
}

void Tetromino::land(GridClass* grid)
{
	//TO-DO add rotation
	for (int fh = 0; fh < shapeSize; fh++) {
		for (int fw = 0; fw < shapeSize; fw++) {
			if (_shape[fh][fw] != 0) {
				grid->placeBlock(_shape[rotation][fh][fw], fw + x, fh + y);
			}
		}
	}
	hasLanded = true;
}

void Tetromino::changeVelocity(unsigned int index, int value)
{
	velocity[index] = value;
}

bool Tetromino::haslanded()
{
	return hasLanded;
}
