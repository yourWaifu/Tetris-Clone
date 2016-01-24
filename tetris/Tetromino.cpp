#include "Tetromino.h"


Tetromino::Tetromino(int h, int w, Uint8(&_shape)[4][4][4], Uint8 _color, WallKickData &_WallKickData)
{
	_h = h;
	_w = w;
	shapeSize = h < w ? w : h;
	rotation = 0;
	velocity[0] = 0; velocity[1] = 0;
	shape = &_shape;
	color = _color;
	WallKick_Data = &_WallKickData;
	canFloorKick = true;
}

Tetromino::Tetromino()
{
}

Tetromino::~Tetromino()
{
}

//void Tetromino::defineShape(int (&shape)[4][4][4])
//{
//	for (size_t r = 0; r < 4; r++) {
//		for (size_t h = 0; h < 4; h++)
//			for (size_t w = 0; w < 4; w++) {
//				_shape[r][h][w] = shape[r][h][w];
//			}
//	}
//}

void Tetromino::draw(SDL_Renderer* renderer)
{
	/*int c = 0;		//color variable
	for (int h = 0; c <= 0 && h < shapeSize; h++) {
		for (int w = 0; w < shapeSize && c <= 0; w++) {
			c += (*shape)[rotation][h][w];
		}
	}*/
	
	setDrawColor(renderer, color);
	drawShape(renderer);
	
}

void Tetromino::drawShape(SDL_Renderer* renderer, bool SrippledAlpha)
{
	for (int fh = 0; fh < shapeSize; fh++) {
		for (int fw = 0; fw < shapeSize; fw++) {
			if ((*shape)[rotation][fh][fw] > 0) {
				Block b;
				b.draw(renderer, (x + fw) * 20, (y + fh) * 20, SrippledAlpha);
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
		hasLanded = true;
	velocity[1] = 0;
}

void Tetromino::move(GridClass * grid, int pvelocity)
{
	velocity[0] = pvelocity;
	if (!detectCollision(grid, moving))
		x += velocity[0];
	velocity[0] = 0;
}

void Tetromino::rotate(GridClass * grid, int direction)
{
	int oldRotation = rotation;
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
	if (detectCollision(grid, rotating)) {
		if (!wallKick(grid, direction)) {
			rotation = oldRotation;
		}
	}
}

void Tetromino::hardDrop(GridClass * grid, Tetromino *Hint)
{
	y = Hint->y;
}

bool Tetromino::wallKick(GridClass * grid, int direction)
{
	bool wallkick = false;
	Sint8(*Data)[WallKickData::states][WallKickData::tests][WallKickData::positions] = 0 < direction ? WallKick_Data->clockwiseData : WallKick_Data->counterClockwiseData;
	for (int testNumber = 1; testNumber < WallKickData::tests; testNumber++) {
		velocity[0] = (*Data)[rotation][testNumber][0];
		velocity[1] = (*Data)[rotation][testNumber][1];
		if (!detectCollision(grid, rotating) && !(!canFloorKick && velocity[1] < 0)) {
			x += velocity[0];
			y += velocity[1];
			if (velocity[1] < 0)
				canFloorKick = false;
			wallkick = true;
			break;
		}
	}
	velocity[0] = 0;
	velocity[1] = 0;
	return wallkick;
}

void Tetromino::changeFallSpeed(int fallSpeed)
{
	_fallSpeed = fallSpeed;
}

bool Tetromino::detectCollision(GridClass* grid, reason theReason)
{
	for (int fh = shapeSize - 1; -1 < fh; fh--) {
		for (int fw = 0; fw < shapeSize; fw++) {
			if ((*shape)[rotation][fh][fw] != 0) {		//checks if there is a block in tetromino at fh and fw
				int blockx = x + fw;
				int blocky = y + fh;
				int newx = blockx + velocity[0];
				int newy = blocky + velocity[1];
				if ((theReason == moving || theReason == rotating) && (newx < 0 || newx > GridClass::w - 1))
					return true;
				if ((theReason == falling || theReason == rotating) && newy > GridClass::h - 1)
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

void Tetromino::lock(GridClass* grid)
{
	//TO-DO add rotation
	for (int fh = 0; fh < shapeSize; fh++) {
		for (int fw = 0; fw < shapeSize; fw++) {
			if ((*shape)[rotation][fh][fw] != 0) {
				grid->placeBlock((*shape)[rotation][fh][fw], fw + x, fh + y);
			}
		}
	}
	isLocked = true;
	canFloorKick = true;	//This doesn't need to be here, but I'm doing it just in case there is a bug with the floorkick
}

//void Tetromino::changeVelocity(unsigned int index, int value)
//{
//	velocity[index] = value;
//}

bool Tetromino::returnIsLocked()
{
	return isLocked;
}

bool Tetromino::returnHasLanded()
{
	return hasLanded;
}

void Tetromino::land(GridClass* grid, Uint32 timeToLock, Uint32 currentTime)
{
	velocity[1] = 1;											//we aren't using velocity as speed but telling the detectCollision function to check if the Tetromino on top of anything
	hasLanded = detectCollision(grid, falling) ? true : false;	//because we are checking Collision by faking a move down the Tetromino, we using the falling reason. if we detect collision, then the Tetromino has landed, else the Tetromino isn't on ground and in the air
	velocity[1] = 0;											//this is prevent any bugs, becuase I use the velocity variable for few things
	if ((timeToLock <= currentTime) && hasLanded) lock(grid);	//if it's time to lock and the Tetromino is on ground then we lock it
}

WallKickData::WallKickData(Sint8(&_clockwiseData)[4][5][2], Sint8(&_counterClockwiseData)[4][5][2])
{
	clockwiseData = &_clockwiseData;
	counterClockwiseData = &_counterClockwiseData;
}

WallKickData::WallKickData()
{

}