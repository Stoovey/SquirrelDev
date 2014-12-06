#ifndef _GAMESTATE_
#define _GAMESTATE_

#include <SDL.h>

/* class which all states must inherit from */
class GameState {

public:
	//this needs to be here or no child class destructors will call
	virtual ~GameState() {};

	//child classes must provide these (they are pure virtual functions as indicated by the "= 0" )
	virtual void Update(unsigned int deltaTime) = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;
};

#endif