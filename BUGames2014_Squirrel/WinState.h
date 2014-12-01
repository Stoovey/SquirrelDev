#ifndef _WINSTATE_
#define _WINSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "CharacterManager.h"

class WinState : public GameState {

public:
	WinState(CharacterManager* players, GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight);
	~WinState();

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	CharacterManager* players;
	GamestateManager* stateManager;
	SDL_Renderer* renderer;
	InputManager* input;

	Sprite* background;
	 
	int winWidth;
	int winHeight;

};

#endif