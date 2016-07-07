#include "InputComponent.h"

std::vector<InputAction*> listOfKeys;

InputAction::InputAction(const char* _name, SDL_Keycode _key, SDL_Keycode _key2)
{
	init(_name, _key, _key2);
}

InputAction::InputAction(const char * _name)
{
	name = _name;
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
}

void makeNewKey(InputAction* newKey, const char * _name, SDL_Keycode _key, SDL_Keycode _key2)
{
	newKey->init(_name, _key, _key2);
	listOfKeys.push_back(newKey);
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
	} else if (inputToBind->key[1] == _event->key.keysym.sym) {
		inputToBind->key[1] = NULL;
	} else {
		inputToBind->key[1] = _event->key.keysym.sym;
	}
	std::string key0ToString = inputToBind->key[0] == NULL ? "" : SDL_GetKeyName(inputToBind->key[0]);
	std::string key1ToString = inputToBind->key[1] == NULL ? "" : SDL_GetKeyName(inputToBind->key[1]);
	*val = inputToBind->name + ' ' + key0ToString + ", " + key0ToString;
	free(_event);
	return nullptr;
}

