#ifndef _WINSTATE_
#define _WINSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Config.h"
#include "Sprite.h"
#include "CharacterManager.h"

/* WinState comes on when a player wins the game */
class WinState : public GameState {

public:
	//constructor / destructor
	WinState(Services* services);
	~WinState();

	//update and draw this stage
	bool Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	Config* config;							//current engine config
	CharacterManager* characterManager;		//pointer to the class which manages the players
	GamestateManager* stateManager;			//allow state changes
	SDL_Renderer* renderer;					//used in sprite creation
	InputManager* input;					//allow this state to access player input

	Sprite* background;				//background used by this state
};

#endif