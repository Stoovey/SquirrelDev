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

class ActionState : public GameState {

public:
	ActionState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int startingPadId, int winWidth, int winHeight);
	~ActionState();

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:

	void CheckHasAnyoneWon();

	CharacterBase* testCharacter;
	InputManager* input;
	Collision* collision;
	level* theLevel;
	SDL_Renderer* renderer;

	std::vector<TiledScrollingBkg*> backgrounds;

	GamestateManager* stateManager;
	CharacterManager* characterManager;
	ItemManager* itemManager;

	int winHeight;
	int winWidth;

	void DoCollisions();
	void DoPlayerAttacks();
};

#endif