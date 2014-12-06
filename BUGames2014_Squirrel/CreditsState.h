#ifndef _CREDITSSTATE_
#define _CREDITSSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Sprite.h"

/* CreditsState just displays the credits image */
class CreditsState : public GameState {

public:
	//constructor / destructor
	CreditsState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight);
	~CreditsState();

	//update and draw this state
	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	GamestateManager* stateManager;	//allow this state to cause state changes
	SDL_Renderer* renderer;			//used to make sprites in here
	InputManager* input;			//used to allow this state to access player input

	Sprite* background;	//background image with credits on
	 
	//width / height of SDL window
	int winWidth;
	int winHeight;
};

#endif