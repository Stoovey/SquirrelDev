#ifndef _MENUSTATE_
#define _MENUSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "menu.h"
#include "ActionState.h"
#include "CreditsState.h"
#include "InputManager.h"
#include "TiledScrollingBkg.h"

class MenuState : public GameState {

public:
	MenuState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight);
	~MenuState();

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	std::vector<TiledScrollingBkg*> backgrounds;

	GamestateManager* stateManager;
	SDL_Renderer* renderer;
	InputManager* input;
	
	Sprite* background;
	Menu* menu;

	int winWidth;
	int winHeight;

};

#endif