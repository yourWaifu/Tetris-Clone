#pragma once
#include <SDL\SDL.h>

#define NUM_OF_GSLICES_IN_ONE_G 65536

Uint32 roundDoubleIntoUInt(double value);

struct SpeedTimingData
{
	int getIndexFromLevel(int level, unsigned int *data, const size_t numOfLevels, const size_t numOfTypesPlusLevel);
};
struct InternalGravity : public SpeedTimingData {
	const static unsigned int numOfLevels = 30;
	const static unsigned int numOfTypesPlusLevel = 2;
	/*
	this is the data for the gravity
	gravity is expressed in 1/65536 of the unit G.
	1G = 1 cell per frame, and 0.1G = 1 cell per 10 frames.
	example
	1024 = 1/64 g	64 * 16ms(1 frame of 60fps) = 1024ms per cell
	or 1024/65536 = 0.015625	1/0.015625 = 64 * 16ms = 1024ms per cell
	*	in the 1st column of data is the level to get the gravity value that's next to in memory
	*	in the 2nd calumn of data is the internal Gravity
	we can hardcode the ms per cell, but for now lets just use 1/65536 of a G
	*/
	unsigned int (*data)[numOfLevels][numOfTypesPlusLevel];
	Uint32 getRawDataFromLevel(int level);
	double getConvertedDataFromLevel(Uint64 frequency, int level);
	Uint32 getRoundedAndConvertedDataFromLevel(Uint64 frequency, int level);
};
struct Delays : public SpeedTimingData {
	enum Type {
		level,
		DAS,
		Lock
	};
	const static unsigned int numOfLevels = 9;
	const static unsigned int numOfTypesPlusLevel = 3;
	/*
	This is for any delay the game
	delays are expressed in 1/60 a.k.a. one frame of 60fps
	data was taken from http://tetris.wikia.com/wiki/Tetris_The_Grand_Master_3_Terror-Instinct
	*/
	unsigned int(*data)[numOfLevels][numOfTypesPlusLevel];
	int getRawDataFromLevel(int level, Type type);
	double getConvertedDataFromLevel(Uint64 frequency, int level, Type type);
	Uint32 getRoundedAndConvertedDataFromLevel(Uint64 frequency, int level, Type type);
};