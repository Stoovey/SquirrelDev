#ifndef _ITEMMANAGER_
#define _ITEMMANAGER_

#include <vector>
#include "ServiceBase.h"
#include "ItemBase.h"
#include "AcornItem.h"
#include "GoalItem.h"
#include "LevelManager.h"
#include "CharacterManager.h"

class ItemManager : public ServiceBase {

public:
	ItemManager(Services* services);
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
	LevelManager* theLevel;
	CharacterManager* characterManager;
	SDL_Renderer* renderer; //needed for item ctors
};

#endif