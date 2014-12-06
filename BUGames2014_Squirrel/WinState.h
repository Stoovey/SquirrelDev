#ifndef _WINSTATE_
#define _WINSTATE_

#include "Gamestate.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "Sprite.h"
#include "CharacterManager.h"

/* WinState comes on when a player wins the game */
class WinState : public GameState {

public:
	//constructor / destructor
	WinState(CharacterManager* players, GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight);
	~WinState();

	//update and draw this stage
	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	CharacterManager* players;		//pointer to the class which manages the players
	GamestateManager* stateManager; //pointer to stateManager
	SDL_Renderer* renderer;			//used in sprite creation
	InputManager* input;			//allow this state to access player input

	Sprite* background;				//background used by this state
	 
	//width and height of SDL window
	int winWidth;
	int winHeight;

};

#endif