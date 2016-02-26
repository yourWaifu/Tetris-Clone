#include "time.h"

Uint64 initialTime;

Uint64 Sys_Time()
{
	if (!initialTime) {
		initialTime = svcGetSystemTick();
	}
	u64 curTime = svcGetSystemTick();
	return curTime - initialTime;
}

Uint32 SDL_GetTicks()
{
	return (Uint32)(Sys_Time() / TICKS_PER_MILLISEC);
}

Uint64 SDL_GetPerformanceCounter()
{
	return Sys_Time();
}

Uint64 SDL_GetPerformanceFrequency()
{
	return TICKS_PER_SEC;
}
