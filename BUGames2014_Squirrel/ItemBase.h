#ifndef _ITEMBASE_
#define _ITEMBASE_

#include "baseObjects.h"
#include "Vector2D.h"
#include "level.h"
#include "CharacterManager.h"
#include "Collision.h"
#include "InputManager.h"

enum ItemState {
	Standard, Fall, Collected, Die, Thrown
};

class ItemBase {

public:
	ItemBase(level* theLevel, CharacterManager* playerManager, InputManager* input);
	~ItemBase();

	virtual void Update(unsigned int deltaTime) = 0;
	virtual void Draw(SDL_Renderer* renderer) = 0;

	virtual void Spawn(int x, int y) = 0;
	virtual void Destroy() = 0;

	Vector2D& GetPos() { return pos; }
	virtual int GetWidth() = 0;
	virtual int GetHeight() = 0;

	ItemState GetItemState() { return itemState; }

protected:
	ItemState itemState;
	level* theLevel;
	CharacterManager* playerManager;
	InputManager* input;
	Collision* collision;

	//pos / move data
	Vector2D pos;
	Vector2D vel;

	//lifetime control
	bool hasFiniteLifespan;
	unsigned int lifespanMS;
};

#endif