#include "input.h"

SDL_Keyboard SDL_keyboard;

SDL_Scancode threeDSInputToSDL_Scancode[32] = { SDL_SCANCODE_K , SDL_SCANCODE_J , SDL_SCANCODE_RSHIFT, SDL_SCANCODE_KP_ENTER,
SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT, SDL_SCANCODE_UP, SDL_SCANCODE_DOWN,
SDL_SCANCODE_R, SDL_SCANCODE_L, SDL_SCANCODE_I, SDL_SCANCODE_U,
SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_7, SDL_SCANCODE_8,
SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,
SDL_SCANCODE_T, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN, SDL_SCANCODE_UNKNOWN,
SDL_SCANCODE_V, SDL_SCANCODE_B, SDL_SCANCODE_N, SDL_SCANCODE_M,
SDL_SCANCODE_D, SDL_SCANCODE_A, SDL_SCANCODE_W, SDL_SCANCODE_S
};

SDL_Keycode threeDSInputToSDL_Keycode[32] = { 'k', 'j' , SDLK_RSHIFT, SDLK_KP_ENTER,
SDLK_RIGHT, SDLK_LEFT, SDLK_UP, SDLK_DOWN,
'r', 'l', 'i', 'u',
0, 0, '7', '8',
0, 0, 0, 0,
't', 0, 0, 0,
'v', 'b', 'n', 'm',
'd', 'a', 'w', 's'
};

const char* keyNames[32] = { "A", "B", "SELECT", "START",
"DRIGHT", "DLEFT", "DUP", "DDOWN",
"R", "L", "X", "Y",
"", "", "ZL", "ZR",
"", "", "", "",
"TOUCH", "", "", "",
"CSTICK_RIGHT", "CSTICK_LEFT", "CSTICK_UP", "CSTICK_DOWN",
"CPAD_RIGHT", "CPAD_LEFT", "CPAD_UP", "CPAD_DOWN" 
};

SDL_Scancode SDL_GetScancodeFromKey(SDL_Keycode key)
{
	if ('a' <= key && key <= 'z') return (SDL_Scancode)(key - 93);	// SDLK_a - SDL_SCANCODE_A = 93
	if (key == '0') return SDL_SCANCODE_0;			// SDLK_0 - SDL_SCANCODE_0 != 19
	if ('1' <= key && key <= '9') return (SDL_Scancode)(key - 19);	// SDLK_1 - SDL_SCANCODE_1 = 19
	return (SDL_Scancode)(key ^ SDLK_SCANCODE_MASK);
}

const char* SDL_GetKeyName(SDL_Keycode key) {
	if (key == 0) return 0;
	for (int i = 0; i < 32; i++)
		if (threeDSInputToSDL_Keycode[i] == key)
			return keyNames[i];
}

const Uint8 * SDL_GetKeyboardState(int * numkeys)
{
	SDL_Keyboard *keyboard = &SDL_keyboard;
	if (numkeys != (int *)0) {
		*numkeys = SDL_NUM_SCANCODES;
	}
	return keyboard->keystate;
}

void SDL_Keyboard::init()
{
	if (!keystate) {
		Uint8 narray[SDL_NUM_SCANCODES];
		std::swap(keystate, narray);
	}
	for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
		keystate[i] = 0;
	}
	didInit = true;
}
