#include "PausedState.h"

//constructor
PausedState::PausedState(Services* services) : GameState(services)
{
	//get any services we need
	this->config       = (Config*)services->GetService(Service::Config);
	this->stateManager = (GamestateManager*)services->GetService(Service::GameStateManager);
	this->input        = (InputManager*)services->GetService(Service::InputManager);
	this->renderer     = services->GetSDL_Renderer();
	
	//create background sprite
	background = new Sprite("Content/UserInterface/background.png", renderer);
}

//destructor
PausedState::~PausedState() {
	//delete everything we have 'new-ed' and stored here
	delete background;
}

//update paused state
bool PausedState::Update(unsigned int deltaTime) {
	
	/* check if escape key or X360 back was pressed, if so then
	 * get stateManager to remove the top state, which will always
	 * be this one if we are running this code */

	if (input->WasKeyPressed(SDLK_ESCAPE)|| input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_BACK) != -1)
		stateManager->RemoveTopState();

	return true;
}

//draw paused state
void PausedState::Draw(SDL_Renderer* renderer) {
	//draw background sprite
	background->Draw(0, 0, config->GetWinWidth(), config->GetWinHeight(), *renderer);
}
