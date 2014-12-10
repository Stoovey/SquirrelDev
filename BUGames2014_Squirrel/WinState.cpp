#include "WinState.h"

WinState::WinState(Services* services) : GameState(services)
{
	//get the services we need
	this->config           = (Config*)services->GetService(Service::Config);
	this->characterManager = (CharacterManager*)services->GetService(Service::CharacterManager);
	this->stateManager     = (GamestateManager*)services->GetService(Service::GameStateManager);
	this->input            = (InputManager*)services->GetService(Service::InputManager);
	this->renderer         = services->GetSDL_Renderer();
	
	//create background this state uses
	background = new Sprite("Content/MainMenu/credits.png", renderer);

}

//destructor
WinState::~WinState() {
	//delete everything we have 'new-ed' and stored in this object
	delete background;
}

//update win state
bool WinState::Update(unsigned int deltaTime) {
	//does nothing, this means there is no way off the win screen
	return true;
}

//draw win state
void WinState::Draw(SDL_Renderer* renderer) {
	//draw the background we use for winstate
	background->Draw(0, 0, config->GetWinWidth(), config->GetWinHeight(), *renderer);
}