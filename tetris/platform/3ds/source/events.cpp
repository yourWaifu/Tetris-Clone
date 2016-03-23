#include "input.h"

SDL_Event Events[MAX_NUM_OF_EVENTS];

int SDL_PollEvent(SDL_Event * _event)
{
	//if (SDL_keyboard.didInit == false) SDL_keyboard.init();
	if (Events[0].type != SDL_FIRSTEVENT) {
		for (int i = 0; i < MAX_NUM_OF_EVENTS; i++) {
			Events[i].type = Events[i + 1].type;
			Events[i].key.keysym.scancode = Events[i + 1].key.keysym.scancode;
			Events[i].key.keysym.sym = Events[i + 1].key.keysym.sym;
		}
		Events[MAX_NUM_OF_EVENTS - 1].type = 0;	//this is just me trying to be careful
			_event->type = Events[0].type;
			_event->key.keysym.scancode = Events[0].key.keysym.scancode;
			_event->key.keysym.sym = Events[0].key.keysym.sym;
		if (Events[0].type != SDL_FIRSTEVENT) return 1;
		else return 0;
	}
	hidScanInput();
	SDL_Keyboard *keyboard = &SDL_keyboard;
	Uint8 eventsMemoryWalker = 0;
	//bool input[32];
	Events[0].type = SDL_FIRSTEVENT;

	Uint32 keyDown = hidKeysDown();
	Uint32 keyUp = hidKeysUp();

	for (int i = 0; i < 32; i++) {
		if (keyUp & BIT(i)) {
			keyboard->keystate[threeDSInputToSDL_Scancode[i]] = 0;
			Events[eventsMemoryWalker].key.keysym.scancode = threeDSInputToSDL_Scancode[i];
			Events[eventsMemoryWalker].key.keysym.sym = threeDSInputToSDL_Keycode[i];
			Events[eventsMemoryWalker].type = SDL_KEYUP;
			++eventsMemoryWalker;
		}
		else if (keyDown & BIT(i)) {
			char str[15];
			keyboard->keystate[threeDSInputToSDL_Scancode[i]] = 1;
			Events[eventsMemoryWalker].key.keysym.scancode = threeDSInputToSDL_Scancode[i];
			Events[eventsMemoryWalker].key.keysym.sym = threeDSInputToSDL_Keycode[i];
			Events[eventsMemoryWalker].type = SDL_KEYDOWN;
			/*if (eventsMemoryWalker == 0) {
				_event->type = SDL_KEYDOWN;
				_event->key.keysym.scancode = threeDSInputToSDL_Scancode[i];
				_event->key.keysym.sym = threeDSInputToSDL_Keycode[i];
			}*/
			++eventsMemoryWalker;
		}
		//else keyboard->keystate[threeDSInputToSDL_Scancode[i]] = 0;
	}
	if (Events[0].type != SDL_FIRSTEVENT) {
		_event->type = Events[0].type;
		_event->key.keysym.scancode = Events[0].key.keysym.scancode;
		_event->key.keysym.sym = Events[0].key.keysym.sym;
		return 1;
	}
	else return 0;
}

int SDL_WaitEvent(SDL_Event * event) {
	int result;
	result = SDL_PollEvent(event);
	while (!result) {
		hidWaitForEvent(HIDEVENT_PAD0, false);
		result = SDL_PollEvent(event);
	}
	return result;
}

bool sys_input_quit(Uint32 type, SDL_Keycode key)
{
	if (type == SDL_KEYDOWN) {
		if (key == SDLK_KP_ENTER) {
			printText("game is now going to close");
			return true;
		}
		else return false;
	}
	else return false;
}
