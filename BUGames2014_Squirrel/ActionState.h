#ifndef _ACTIONSTATE_
#define _ACTIONSTATE_

#include "Services.h"
#include "Gamestate.h"
#include "GamestateManager.h"
#include "TestCharacter.h"
#include "CollisionHelper.h"
#include "LevelManager.h"
#include "Config.h"
#include "CharacterManager.h"
#include "InputManager.h"
#include "TiledScrollingBkg.h"
#include "ItemManager.h"
#include "WinState.h"
#include "PausedState.h"

/* ActionState is what you would think of as the main game
 * screen, with all the players, items, levels etc going on */
class ActionState : public GameState {

public:
	//constructor / destructor
	ActionState(Services* services, int startingPadId);
	~ActionState();

	//called to update or draw ActionState
	bool Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:

	//see if any player has won the game
	bool CheckHasAnyoneWon();

	Config* config;                 //current engine config
	InputManager* input;			//allow ActionState to access player input
	CollisionHelper* collision;		//collision checker
	LevelManager* theLevel;			//the map itself
	SDL_Renderer* renderer;			//allow rendering in SDL

	//collection of pointers to the backgrounds this state uses
	std::vector<TiledScrollingBkg*> backgrounds;

	GamestateManager* stateManager;		 //used to cause state changes from within this state (i.e go to PausedState)
	CharacterManager* characterManager;	 //looks after the the 4 characters in use
	ItemManager* itemManager;			 //looks after the items in use (acorn, goal etc)

	void DoCollisions();	//detect players touching the platforms
	void DoPlayerAttacks();	//detect players attacking each other
};

#endif