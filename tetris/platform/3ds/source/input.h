#pragma once
#include <algorithm>
#include "sys_3ds.h"
#include "SDL_scancode.h"
#include "SDL_keycode.h"
#include "event_types.h"

#define INPUT_H

typedef struct SDL_Keyboard SDL_Keyboard;

typedef struct SDL_Keysym
{
	SDL_Scancode scancode;      /**< SDL physical key code - see ::SDL_Scancode for details */
	SDL_Keycode sym;					/**< SDL virtual key code - see ::SDL_Keycode for details */
} SDL_Keysym;

typedef struct SDL_KeyboardEvent
{
	SDL_Keysym keysym;  /**< The key that was pressed or released */
} SDL_KeyboardEvent;

struct SDL_Keyboard
{
	Uint8 keystate[SDL_NUM_SCANCODES];
	bool didInit;
	void init();
};

extern SDL_Keyboard SDL_keyboard;

extern SDL_Scancode SDL_GetScancodeFromKey(SDL_Keycode key);
const char* SDL_GetKeyName(SDL_Keycode key);
extern const Uint8* SDL_GetKeyboardState(int *numkeys);

typedef union SDL_Event
{
	Uint32 type;					/**< Event type, shared with all events */
	SDL_KeyboardEvent key;			/**< Keyboard event data */
} SDL_Event;

#define MAX_NUM_OF_EVENTS 12

extern SDL_Event Events[MAX_NUM_OF_EVENTS];

extern int SDL_PollEvent(SDL_Event * event);
extern int SDL_WaitEvent(SDL_Event * event);
extern bool sys_input_quit(Uint32 type, SDL_Keycode key);