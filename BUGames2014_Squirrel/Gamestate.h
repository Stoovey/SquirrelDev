#ifndef _GAMESTATE_
#define _GAMESTATE_

#include <SDL.h>

class GameState {

public:

	virtual void Update(unsigned int deltaTime) = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;
};

#endif