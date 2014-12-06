#ifndef _GAMESTATEMANAGER_
#define _GAMESTATEMANAGER_

#include "Gamestate.h"
#include <vector>
#include <SDL.h>

/* GameStateManager deals with updating and drawing the correct 
 * GameStates, and handling the transitions between them. States 
 * are things like ActionState, PausedState, MenuState */
class GamestateManager {

public:
	//destructor
	~GamestateManager();

	//gamestate management functions
	void AddState(GameState* state);
	void RemoveAllStates();
	void RemoveTopState();

	//called to update and draw the states which need it
	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	/* this vector contains a list of pointers to GameState
	 * objects (or objects of any class which inherits GameState),
	 * it does not contain the objects themselves */
	std::vector<GameState*> gameStates;
};

#endif