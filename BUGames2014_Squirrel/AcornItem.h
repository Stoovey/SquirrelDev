#ifndef _ACORNITEM_
#define _ACORNITEM_

#include "ItemBase.h"
#include "Sprite.h"
#include "CharacterBase.h"

class AcornItem : public ItemBase {

public:
	AcornItem(level* theLevel, CharacterManager* playerManager, SDL_Renderer* renderer, InputManager* input);

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

	void Spawn(int x, int y);
	void Destroy();

	void ThrowFromPlayer();

	bool DoGoalCheck(std::vector<ItemBase*>& goalItems);
	CharacterBase* GetPlayerHoldingThis() { return playerHoldingThis; }

private:
	Sprite* acornSprite;

	int GetWidth();
	int GetHeight();

	float throwVelY;
	bool lastMovedLeft;

	void UpdateNormal(unsigned int deltaTime);
	void UpdateFalling(unsigned int deltaTime);
	void UpdateCollected(unsigned int deltaTime);
	void UpdateThrown(unsigned int deltaTime);

	void CheckInBounds();

	Sprite* CheckCollideScenery();
	CharacterBase* CheckCollisionPlayer();

	//playing holding it now and the one before that
	CharacterBase* playerHoldingThis;
	CharacterBase* lastPlayerHoldingThis;
	unsigned int samePlayerHoldingTimer;
	unsigned int samePlayerHoldingTimerReset;
	unsigned int cannotBeHeldTimer;
	unsigned int cannotBeHeldTimerReset;
};

#endif