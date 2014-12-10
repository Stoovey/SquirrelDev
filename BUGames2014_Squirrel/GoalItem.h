#ifndef _GOALITEM_
#define _GOALITEM_

#include "ItemBase.h"

class GoalItem : public ItemBase {

public:
	GoalItem(LevelManager* theLevel, CharacterManager* playerManager, SDL_Renderer* renderer, InputManager* input);
	~GoalItem();

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

	void Spawn(int x, int y);
	void Destroy();
	
	int GetWidth();
	int GetHeight();

private:

	Sprite* goalSprite;
};

#endif