#ifndef _ACTIONSTATE_
#define _ACTIONSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "TestCharacter.h"
#include "Collision.h"
#include "level.h"
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
	ActionState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int startingPadId, int winWidth, int winHeight);
	~ActionState();

	//called to update or draw ActionState
	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:

	//see if any player has won the game
	bool CheckHasAnyoneWon();

	//CharacterBase* testCharacter;	//can represent any type of character
	InputManager* input;			//allow ActionState to access player input
	Collision* collision;			//collision checker
	level* theLevel;				//the map itself
	SDL_Renderer* renderer;			//allow rendering in SDL

	//collection of pointers to the backgrounds this state uses
	std::vector<TiledScrollingBkg*> backgrounds;

	GamestateManager* stateManager;		 //used to cause state changes from within this state (i.e go to PausedState)
	CharacterManager* characterManager;	 //looks after the the 4 characters in use
	ItemManager* itemManager;			 //looks after the items in use (acorn, goal etc)

	//store SDL game window width and height in pixels
	int winHeight;
	int winWidth;

	void DoCollisions();	//detect players touching the platforms
	void DoPlayerAttacks();	//detect players attacking each other
};

#endif