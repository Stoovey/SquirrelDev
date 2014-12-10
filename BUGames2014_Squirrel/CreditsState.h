#ifndef _CREDITSSTATE_
#define _CREDITSSTATE_

#include "Gamestate.h"
#include "Config.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Sprite.h"

/* CreditsState just displays the credits image */
class CreditsState : public GameState {

public:
	//constructor / destructor
	CreditsState(Services* services);
	~CreditsState();

	//update and draw this state
	bool Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	
	Config* config;                 //current engine config
	GamestateManager* stateManager;	//allow this state to cause state changes
	SDL_Renderer* renderer;			//used to make sprites in here
	InputManager* input;			//used to allow this state to access player input

	Sprite* background;	//background image with credits on
};

#endif