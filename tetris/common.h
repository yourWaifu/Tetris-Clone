#pragma once

struct SceenResolution
{
	int w, h;
	int leftSideX;
	float resolutionToOldStandardRatios[2];		//foe the indexs 0 is the Width and 1 is the height
	bool fullscreen;
	void change(int w, int h);
	void updateLeftSideX();
};

extern SceenResolution gameResolution;

int convertStringToIntger(const char* string);