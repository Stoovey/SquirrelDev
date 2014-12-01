#ifndef _CREDITSSTATE_
#define _CREDITSSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Sprite.h"

class CreditsState : public GameState {

public:
	CreditsState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight);
	~CreditsState();

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	GamestateManager* stateManager;
	SDL_Renderer* renderer;
	InputManager* input;

	Sprite* background;
	 
	int winWidth;
	int winHeight;

};

#endif