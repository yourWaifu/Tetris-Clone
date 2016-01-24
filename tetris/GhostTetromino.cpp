#include "Tetromino.h"

GhostTetromino::GhostTetromino()
{
}

GhostTetromino::~GhostTetromino()
{
}

void GhostTetromino::draw(Tetromino T, SDL_Renderer * renderer)
{
	shape = T.shape;
	rotation = T.returnRotation();
	SDL_Color tint;
	tint.a = 85;
	SDL_Color color = getDrawColor(T.returnColor());
	SDL_SetRenderDrawColor(renderer, (Uint8)(((float)tint.a / 255.0f ) * (float)color.r), (Uint8)(((float)tint.a / 255.0f) * (float)color.g), (Uint8)(((float)tint.a / 255.0f) * (float)color.b), 255);
	drawShape(renderer, true);
}

void GhostTetromino::update(GridClass* grid, Tetromino T) {
	x = T.x;
	y = T.y;
	shape = T.shape;
	shapeSize = T.returnShapeSize();
	rotation = T.returnRotation();
	for (int i = 1; i < grid->h; i++) {
		velocity[1] = i;
		if (detectCollision(grid, falling)) {
			y += velocity[1] - 1;
			break;
		}
	}
}