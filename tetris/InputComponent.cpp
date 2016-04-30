#include "InputComponent.h"

InputAction::InputAction(const char* _name, SDL_Keycode _key, SDL_Keycode _key2)
{
	init(_name, _key, _key2);
}


InputAction::InputAction(const char * _name)
{
	name = _name;
	canChangeKey0 = true;
}

InputAction::InputAction()
{
}

InputAction::~InputAction()
{
}

Uint8 InputAction::returnState(const Uint8 * states)
{
	return (states[SDL_GetScancodeFromKey(key[0])] || states[SDL_GetScancodeFromKey(key[1])]);
}

bool InputAction::isEqualTo(SDL_Keycode sym)
{
	return (sym == key[0] || sym == key[1]);
}

void InputAction::init(const char* _name, SDL_Keycode _key, SDL_Keycode _key2)
{
	name = _name;
	key[0] = _key;
	key[1] = _key2;
	if (key[0] != NULL && key[1] == NULL) canChangeKey0 = false;
	else canChangeKey0 = true;
}

void* bind(void* var, std::string* val)
{
	SDL_Event* _event = (SDL_Event*)malloc(sizeof(SDL_Event));
	while (_event->type != SDL_KEYDOWN) {
		SDL_WaitEvent(_event);
	}
	InputAction* inputToBind = (InputAction*)var;
	if (inputToBind->key[0] == _event->key.keysym.sym) {
		inputToBind->key[0] = NULL;
		inputToBind->canChangeKey0 = true;
	} else if (inputToBind->key[1] == _event->key.keysym.sym) {
		inputToBind->key[1] = NULL;
		inputToBind->canChangeKey0 = false;
	} else if (inputToBind->canChangeKey0) {
		inputToBind->key[0] = _event->key.keysym.sym;
		inputToBind->canChangeKey0 = false;
	} else {
		inputToBind->key[1] = _event->key.keysym.sym;
		inputToBind->canChangeKey0 = true;
	}
	std::string key0ToString = inputToBind->key[0] == NULL ? "" : SDL_GetKeyName(inputToBind->key[0]);
	std::string key1ToString = inputToBind->key[1] == NULL ? "" : SDL_GetKeyName(inputToBind->key[1]);
	*val = inputToBind->name + ' ' + key0ToString + ", " + key0ToString;
	free(_event);
	return nullptr;
}
