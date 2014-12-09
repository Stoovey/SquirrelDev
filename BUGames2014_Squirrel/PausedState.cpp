#include "PausedState.h"

//constructor
PausedState::PausedState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight)
{
	//store incoming parameters in memebr vars
	this->stateManager = stateManager;
	this->renderer = renderer;
	this->input = input;
	this->winWidth = winWidth;
	this->winHeight = winHeight;
	
	//create background sprite
	background = new Sprite("Content/UserInterface/background.png", renderer);
}

//destructor
PausedState::~PausedState() {
	//delete everything we have 'new-ed' and stored here
	delete background;
}

//update paused state
void PausedState::Update(unsigned int deltaTime) {
	
	/* check if escape key or X360 back was pressed, if so then
	 * get stateManager to remove the top state, which will always
	 * be this one if we are running this code */

	if (input->WasKeyPressed(SDLK_ESCAPE)|| input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_BACK) != -1)
		stateManager->RemoveTopState();
}

//draw paused state
void PausedState::Draw(SDL_Renderer* renderer) {
	//draw background sprite
	background->Draw(0, 0, winWidth, winHeight, *renderer);
}
