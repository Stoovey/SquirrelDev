#pragma once

#include <SDL.h>
#include <string.h>
#include <iostream>
#include "Sprite.h"
#include "InputManager.h"

class Menu {

public:
	Menu(SDL_Renderer* renderer, InputManager* input);
	~Menu();

	int Update();
	void Draw(SDL_Renderer* renderer);

	int GetSelectingpadId() { return selectingPadId; }

private:
	static const int MENU_ITEM_COUNT;
	InputManager* input;

	Sprite* unselectedImages[3];
	Sprite* selectedImages[3];

	int selectedIndex;
	int selectingPadId;

	void DoSelection();

	void LoadImages(SDL_Renderer* renderer);
};