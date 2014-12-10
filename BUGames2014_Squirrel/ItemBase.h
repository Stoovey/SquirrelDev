#ifndef _ITEMBASE_
#define _ITEMBASE_

#include "baseObjects.h"
#include "Vector2D.h"
#include "LevelManager.h"
#include "CharacterManager.h"
#include "CollisionHelper.h"
#include "InputManager.h"

namespace ItemState {
	enum State {
		Standard, Fall, Collected, Die, Thrown
	};
};

class ItemBase {

public:
	ItemBase(LevelManager* theLevel, CharacterManager* playerManager, InputManager* input);
	~ItemBase();

	virtual void Update(unsigned int deltaTime) = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;

	virtual void Spawn(int x, int y) = 0;
	virtual void Destroy() = 0;

	Vector2D& GetPos() { return pos; }
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;

	ItemState::State GetItemState() { return itemState; }

protected:
	ItemState::State itemState;
	LevelManager* theLevel;
	CharacterManager* playerManager;
	InputManager* input;
	CollisionHelper* collision;

	//pos / move data
	Vector2D pos;
	Vector2D vel;

	//lifetime control
	bool hasFiniteLifespan;
	unsigned int lifespanMS;
};

#endif