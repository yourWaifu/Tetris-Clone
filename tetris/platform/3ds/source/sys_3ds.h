#pragma once
#include <3ds.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define SYSH true
#define USE_RAND
#define CONSOLE_INTERFACE

/**
*  \name Basic data types
*/
/* @{ */

typedef enum
{
	SDL_FALSE = 0,
	SDL_TRUE = 1
} SDL_bool;

/**
* \brief A signed 8-bit integer type.
*/
typedef int8_t Sint8;
/**
* \brief An unsigned 8-bit integer type.
*/
typedef uint8_t Uint8;
/**
* \brief A signed 16-bit integer type.
*/
typedef int16_t Sint16;
/**
* \brief An unsigned 16-bit integer type.
*/
typedef uint16_t Uint16;
/**
* \brief A signed 32-bit integer type.
*/
typedef int32_t Sint32;
/**
* \brief An unsigned 32-bit integer type.
*/
typedef uint32_t Uint32;

/**
* \brief A signed 64-bit integer type.
*/
typedef int64_t Sint64;
/**
* \brief An unsigned 64-bit integer type.
*/
typedef uint64_t Uint64;

/* @} *//* Basic data types */

#ifndef ALLHFILES
#define ALLHFILES
#include "video.h"
#include "render.h"
#include "events.h"
#include "time.h"
#include "input.h"
#endif // !ALLHFILES