#include "WinState.h"

WinState::WinState(CharacterManager* players, GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight)
{
	//store incoming vars in member vars
	this->players = players;
	this->stateManager = stateManager;
	this->renderer = renderer;
	this->input = input;
	this->winWidth = winWidth;
	this->winHeight = winHeight;
	
	//create background this state uses
	background = new Sprite("Content/MainMenu/credits.png", renderer);

}

//destructor
WinState::~WinState() {
	//delete everything we have 'new-ed' and stored in this object
	delete background;
}

//update win state
void WinState::Update(unsigned int deltaTime) {
	//does nothing, this means there is no way off the win screen
}

//draw win state
void WinState::Draw(SDL_Renderer* renderer) {
	//draw the background we use for winstate
	background->Draw(0, 0, winWidth, winHeight, *renderer);
}