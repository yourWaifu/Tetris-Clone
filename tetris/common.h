#pragma once

struct SceenResolution
{
	int w, h;
	float resolutionToOldStandardRatios[2];		//foe the indexs 0 is the Width and 1 is the height
	void change(int w, int h);
};

extern SceenResolution gameResolution;

void updateLeftSideX();
extern int leftSideX;