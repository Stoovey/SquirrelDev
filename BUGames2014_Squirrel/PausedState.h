#ifndef _PAUSEDSTATE_
#define _PAUSEDSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "Config.h"
#include "InputManager.h"
#include "Sprite.h"

/* PausedState get put on when ActionState id paused */
class PausedState : public GameState {

public:
	//constructor / destructor
	PausedState(Services* services);
	~PausedState();

	//update and draw this state
	bool Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	Config* config;                 //current engine config
	GamestateManager* stateManager;	//allow state changes from this state
	SDL_Renderer* renderer;			//used in sprite creation
	InputManager* input;			//allow this state to access player input

	Sprite* background;				//background image used by this state
};

#endif