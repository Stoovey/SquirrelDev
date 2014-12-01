#include "MenuState.h"
#include <iostream>

MenuState::MenuState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight) {
	this->stateManager = stateManager;
	this->renderer = renderer;
	this->input = input;
	this->winWidth = winWidth;
	this->winHeight = winHeight;

	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Background_scaled.png", renderer), .01f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Clouds_scaled.png", renderer), .03f, winWidth, winHeight));
	background = new Sprite("Assets/mainmenu_transparent.png", renderer);
	menu = new Menu(renderer, input);
}

MenuState::~MenuState() {
	delete background;
	delete menu;
}

void MenuState::Update(unsigned int deltaTime) {
	int menuChoice = -1;
		
	menuChoice = menu->Update();

	if (menuChoice == 0) {
		stateManager->RemoveAllStates();
		int startingPadId = menu->GetSelectingpadId();
		if (startingPadId == -1)
			stateManager->AddState(new ActionState(stateManager, renderer, input, 0, winWidth, winHeight));
		else
			stateManager->AddState(new ActionState(stateManager, renderer, input, startingPadId,  winWidth, winHeight));
	}
	else if (menuChoice ==1 ) {
		//credits
		stateManager->AddState(new CreditsState(stateManager, renderer, input, winWidth, winHeight));
	}
	else if (menuChoice == 2)
	{
		//quit
		exit(0);
	}

	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Update(deltaTime);

}

void MenuState::Draw(SDL_Renderer* renderer) {
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Draw(renderer);

	background->Draw(0, 0, winWidth, winHeight, *renderer);
	menu->Draw(renderer);
}

