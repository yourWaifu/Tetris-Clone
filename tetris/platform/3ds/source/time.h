#pragma once
#include <3ds.h>
#include "sys_3ds.h"

#define TICKS_PER_SEC 268123480.0
#define TICKS_PER_MILLISEC 268123.4800
extern Uint64 initialTime;

Uint64 Sys_Time();
Uint32 SDL_GetTicks();
Uint64 SDL_GetPerformanceCounter();
Uint64 SDL_GetPerformanceFrequency();