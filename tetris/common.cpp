#include "common.h"

SceenResolution gameResolution;

void SceenResolution::change(int _w, int _h) {
	w = _w;
	h = _h;
	resolutionToOldStandardRatios[0] = w / 480.0f;
	resolutionToOldStandardRatios[1] = h / 480.0f;
}