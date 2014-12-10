#include "CreditsState.h"

//constructor
CreditsState::CreditsState(Services* services) : GameState(services)
{
	//get services we need
	this->config       = (Config*)services->GetService(Service::Config);
	this->stateManager = (GamestateManager*)services->GetService(Service::GameStateManager);
	this->input        = (InputManager*)services->GetService(Service::InputManager);
	this->renderer     = services->GetSDL_Renderer();

	//create background sprite
	background = new Sprite("Content/MainMenu/credits.png", renderer);

}

//destructor
CreditsState::~CreditsState() {
	//delete everything we 'new-ed' and stored in this state
	delete background;
}

//update this state
bool CreditsState::Update(unsigned int deltaTime) {
	
	/* if escape or X360 Back are pressed by anyone then
	 * then tell stateManager to remove the 'top' state
	 * (last in states list) which will be this one. 
	 * (only the top state updates so it must be this one) */

	if (input->WasKeyPressed(SDLK_ESCAPE))
		stateManager->RemoveTopState();
	else if(input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_BACK) != -1)
		stateManager->RemoveTopState();

	return true;
}

//draw this state
void CreditsState::Draw(SDL_Renderer* renderer) {
	//draw the background sprite
	background->Draw(0, 0, config->GetWinWidth(), config->GetWinHeight(), *renderer);
}
