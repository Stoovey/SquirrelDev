#include "CreditsState.h"

//constructor
CreditsState::CreditsState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight)
{
	//store incoming parameters in member vars
	this->stateManager = stateManager;
	this->renderer = renderer;
	this->input = input;
	this->winWidth = winWidth;
	this->winHeight = winHeight;
	
	//create background sprite
	background = new Sprite("Content/MainMenu/credits.png", renderer);

}

//destructor
CreditsState::~CreditsState() {
	//delete everything we 'new-ed' and stored in this state
	delete background;
}

//update this state
void CreditsState::Update(unsigned int deltaTime) {
	
	/* if escape or X360 Back are pressed by anyone then
	 * then tell stateManager to remove the 'top' state
	 * (last in states list) which will be this one. 
	 * (only the top state updates so it must be this one) */

	if (input->WasKeyPressed(SDLK_ESCAPE))
		stateManager->RemoveTopState();
	else if(input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_BACK) != -1)
		stateManager->RemoveTopState();
}

//draw this state
void CreditsState::Draw(SDL_Renderer* renderer) {
	//draw the background sprite
	background->Draw(0, 0, winWidth, winHeight, *renderer);
}
