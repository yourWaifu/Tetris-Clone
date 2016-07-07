#pragma once
#include <sys.h>
#include <string>
#include <vector>
//move all input stuff here, later
//remember that this will be a pointer in the gameclass

struct InputAction
{
public:
	InputAction(const char* _name, SDL_Keycode _key, SDL_Keycode _key2 = NULL);
	InputAction(const char* _name);
	InputAction();
	~InputAction();
	Uint8 returnState(const Uint8* states);
	Uint8 returnNotState(const Uint8* states);
	bool isEqualTo(SDL_Keycode sym);
	void init(const char* _name, SDL_Keycode _key, SDL_Keycode _key2 = NULL);
	void fullBind(SDL_Keycode _key, SDL_Keycode _key2 = NULL);
	void bind(SDL_Keycode _key);
	bool power;
	const char* name;
	SDL_Keycode key[2];
private:
};

extern std::vector<InputAction*> listOfKeys;

void makeNewKey(InputAction* newKey, const char * _name, SDL_Keycode _key, SDL_Keycode _key2 = NULL);
extern void* bind(void*, std::string* val);
