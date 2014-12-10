#ifndef _MENUSTATE_
#define _MENUSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "menu.h"
#include "Config.h"
#include "ActionState.h"
#include "CreditsState.h"
#include "InputManager.h"
#include "TiledScrollingBkg.h"

/* MenuState is the one with the front end menu on.
 * This is the state the game starts in */
class MenuState : public GameState {

public:
	//constructor / destructor
	MenuState(Services* services);
	~MenuState();

	//update and draw this state
	bool Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	//collection of pointers to the backgrounds this state uses
	std::vector<TiledScrollingBkg*> backgrounds;

	Config* config;                 //current engine config
	GamestateManager* stateManager;	//used to cause state changes from within this state (i.e go to PausedState)
	SDL_Renderer* renderer;			//used in sprite creation
	InputManager* input;			//allow MenuState to access player input
	Sprite* background;				//main background image (see constructor for details)
	Menu* menu;						//pointer to the menu itself
};

#endif