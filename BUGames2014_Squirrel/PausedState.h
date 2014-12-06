#ifndef _PAUSEDSTATE_
#define _PAUSEDSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Sprite.h"

/* PausedState get put on when ActionState id paused */
class PausedState : public GameState {

public:
	//constructor / destructor
	PausedState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight);
	~PausedState();

	//update and draw this state
	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	GamestateManager* stateManager;	//allow state changes from this state
	SDL_Renderer* renderer;			//used in sprite creation
	InputManager* input;			//allow this state to access player input

	Sprite* background;				//background image used by this state
	 
	//width and height of SDL window
	int winWidth;
	int winHeight;
};

#endif