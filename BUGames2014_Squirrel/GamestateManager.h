#ifndef _GAMESTATEMANAGER_
#define _GAMESTATEMANAGER_

#include "Gamestate.h"
#include <vector>
#include <SDL.h>

class GamestateManager {

public:

	~GamestateManager();

	void AddState(GameState* state);
	void RemoveAllStates();
	void RemoveTopState();

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	std::vector<GameState*> gameStates;
};

#endif