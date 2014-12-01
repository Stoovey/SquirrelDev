#include "CreditsState.h"

CreditsState::CreditsState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight)
{
	this->stateManager = stateManager;
	this->renderer = renderer;
	this->input = input;
	this->winWidth = winWidth;
	this->winHeight = winHeight;
	
	background = new Sprite("images/credits/credits.png", renderer);

}

CreditsState::~CreditsState() {

}

void CreditsState::Update(unsigned int deltaTime) {
	//system("cls");
	//std::cout << "Credits Update" << std::endl;
	if (input->WasKeyPressed(SDLK_ESCAPE))
		stateManager->RemoveTopState();
	else if(input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_BACK) != -1)
		stateManager->RemoveTopState();
}

void CreditsState::Draw(SDL_Renderer* renderer) {
	//std::cout << "Credits Draw" << std::endl;
	background->Draw(0, 0, winWidth, winHeight, *renderer);
}
