#include "WinState.h"

WinState::WinState(CharacterManager* players, GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight)
{
	this->players = players;
	this->stateManager = stateManager;
	this->renderer = renderer;
	this->input = input;
	this->winWidth = winWidth;
	this->winHeight = winHeight;
	
	background = new Sprite("images/credits/credits.png", renderer);

}

WinState::~WinState() {

}

void WinState::Update(unsigned int deltaTime) {
	//system("cls");
	//std::cout << "Credits Update" << std::endl;
	//if (input->WasKeyPressed(SDLK_ESCAPE))
	//	stateManager->RemoveTopState();
}

void WinState::Draw(SDL_Renderer* renderer) {
	//std::cout << "Credits Draw" << std::endl;
	background->Draw(0, 0, winWidth, winHeight, *renderer);
}
