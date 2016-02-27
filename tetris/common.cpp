#include "common.h"

SceenResolution gameResolution;

void SceenResolution::change(int _w, int _h) {
	w = _w;
	h = _h;
	resolutionToOldStandardRatios[0] = w / 480.0f;
	resolutionToOldStandardRatios[1] = h / 480.0f;
	updateLeftSideX();
}

void SceenResolution::updateLeftSideX()
{
	leftSideX = (gameResolution.w - (int)(302.0 * gameResolution.resolutionToOldStandardRatios[1])) / 2;
}