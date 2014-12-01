#ifndef _ITEMMANAGER_
#define _ITEMMANAGER_

#include <vector>
#include "ItemBase.h"
#include "AcornItem.h"
#include "GoalItem.h"
#include "level.h"
#include "CharacterManager.h"

class ItemManager {

public:
	ItemManager(level* thelevel, CharacterManager* playerManager, SDL_Renderer* renderer, InputManager* input);
	~ItemManager();

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

	void SpawnAcorn();
	void SpawnGoal();
	AcornItem* GetAcornItem() { return acornItem; }

private:
	std::vector<ItemBase*> spawnedItems; //may get replaced
	std::vector<ItemBase*> goalItems;
	AcornItem* acornItem;

	InputManager* input;
	level* theLevel;
	CharacterManager* playerManager;
	SDL_Renderer* renderer; //needed for item ctors
};

#endif