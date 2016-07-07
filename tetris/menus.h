#pragma once
#include <sys.h>
#include <string>
#include <array>
#include <vector>
#ifdef SDL
#include "platform/windows/TextComponent.h"
#endif
#include "common.h"

class MenuObject {
public:
	std::string name;
	std::string description;
	std::string value;
	virtual bool isThisAMenu() { return false; }
};

class NormalMenu : public MenuObject {
public:
	NormalMenu(const std::string _name, const std::string _description, std::vector<MenuObject*>* _menuList);
	virtual void draw(SDL_Renderer* renderer, const unsigned int* menuSelectIndex, TextComponent* UIText);
	unsigned int getSize();
	virtual bool isThisAMenu() { return true; }
	std::vector<MenuObject*>* menuList;
	bool magic = false;
};

class MenuAction : public MenuObject {
public:
	MenuAction(std::string _name, std::string _description, void(*_doAction)(void*, const std::string, std::string*), void* _variableToEdit, std::string _value = "");
	void (*doAction)(void*, const std::string, std::string*);
	void* getVariablePointer() { return variableToEdit; }
protected:
	void* variableToEdit;
};

class DropdownMenu : public NormalMenu {
public:
	DropdownMenu(std::string _name, std::string _description, std::vector<MenuObject*> _menuList);
	virtual void draw(SDL_Renderer* renderer);
};

struct Path{
	public:
	Path(NormalMenu* _location[8], unsigned int _objectIndex = 0);
	NormalMenu* getCurrentMenu();
	Uint8 numOfObjectsInLocationArray;
	NormalMenu* location[8];
	unsigned int selectIndex;
};

Path* makeNewPath(NormalMenu* start);

//add sliders or whatever it's called, can be limmited and can't go in between numbers if variable > 0, if variable == 0 then you can go in between numbers
//add a speal type of menu for chagning controls
//to-do have tabs at the top for previous menu