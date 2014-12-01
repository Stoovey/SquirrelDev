#ifndef _PAUSEDSTATE_
#define _PAUSEDSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Sprite.h"

class PausedState : public GameState {

public:
	PausedState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight);
	~PausedState();

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