#include "menus.h"

MenuAction::MenuAction(std::string _name, std::string _description, void(*_doAction)(void*, std::string*), void* _variableToEdit, std::string _value)
{
	name = _name;
	description = _description;
	value = _value;
	doAction = _doAction;
	variableToEdit = _variableToEdit;
}

NormalMenu::NormalMenu(std::string _name, std::string _description, std::vector<MenuObject*>* _menuList)
{
	name = _name;
	description = _description;
	value = "";
	menuList = _menuList;
	if (menuList != nullptr) magic = true;
}

void NormalMenu::draw(SDL_Renderer * renderer, const unsigned int* menuSelectIndex, TextComponent* UIText)
{
	/*SDL_Rect background = { 0, 0, 200, 200 };
	SDL_SetRenderDrawColor(renderer, 255, 0, 0);
	SDL_RenderFillRect(renderer, &background);*/
	UIText->draw(renderer, name.c_str(), 0, 0);
	for (unsigned int i = 0; i < menuList->size(); i++) {
		//if (i == *menuSelectIndex) UIText->changeColor(255, 0, 0);
		std::string text = i == *menuSelectIndex ? ">" : "";
		text += menuList->at(i)->name + "    " + menuList->at(i)->value;
		UIText->draw(renderer, text.c_str(), 20, i*20+20);
		//UIText->changeColor(255, 255, 255);
	}
}

unsigned int NormalMenu::getSize()
{
	return menuList->size();
}

Path::Path(NormalMenu* _location[8], unsigned int _objectIndex) {
	int i = 0;
	numOfObjectsInLocationArray = 0;
	for (; i < 8; i++) {
		if (_location[i]->magic) numOfObjectsInLocationArray++;
		location[i] = _location[i];
	}
	selectIndex = _objectIndex;
}

NormalMenu* Path::getCurrentMenu() {
	return location[numOfObjectsInLocationArray - 1];
}

Path* makeNewPath(NormalMenu* start)
{
	Path* newPath = (Path*)calloc(1, sizeof(*newPath));
	for (int i = 0; i < 8; i++) {	//fill the array with juck, becuase if we don't the game will try to access a null object
		NormalMenu m("", "", nullptr);
		//m.name = "";
		//m.description = "";
		//m.menuList = nullptr;
		//m.magic = false;
		newPath->location[i] = &m;
	}
	newPath->location[0] = start;
	newPath->numOfObjectsInLocationArray = 1;
	newPath->selectIndex = 0;
	return newPath;
}
