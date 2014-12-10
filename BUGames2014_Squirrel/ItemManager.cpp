#include "ItemManager.h"

ItemManager::ItemManager(Services* services) {

	//store any services we need
	this->theLevel         = (LevelManager*)services->GetService(Service::LevelManager);
	this->characterManager = (CharacterManager*)services->GetService(Service::CharacterManager);
	this->input            = (InputManager*)services->GetService(Service::InputManager);
	this->renderer         = services->GetSDL_Renderer();

	SpawnGoal();
}

ItemManager::~ItemManager() {
	std::vector<ItemBase*>::iterator iter;
	for (iter = spawnedItems.begin(); iter != spawnedItems.end(); iter++)
		delete (*iter);
}

void ItemManager::Update(unsigned int deltaTime) {
	std::vector<ItemBase*>::iterator iter;
	for (iter = spawnedItems.begin(); iter != spawnedItems.end(); iter++)
		(*iter)->Update(deltaTime);

	if (acornItem->DoGoalCheck(goalItems))
		SpawnGoal();

	if (acornItem->GetItemState() == ItemState::Die) {
		std::vector<ItemBase*>::iterator iter;
		for (iter = spawnedItems.begin(); iter != spawnedItems.end(); iter++) {
			if ((*iter) == acornItem) {
				spawnedItems.erase(iter);
				acornItem = NULL;
				break;
			}
		}

		SpawnAcorn();
	}
}

void ItemManager::Draw(SDL_Renderer* renderer) {
	std::vector<ItemBase*>::iterator iter;
	for (iter = spawnedItems.begin(); iter != spawnedItems.end(); iter++)
		(*iter)->Draw(renderer);
}

void ItemManager::SpawnAcorn() {

	acornItem = new AcornItem(theLevel, characterManager, renderer, input);
	acornItem->Spawn((rand() % 1080) + 100, 0);
	spawnedItems.push_back(acornItem);
}

void ItemManager::SpawnGoal() {
	//hacky, clears goalItems vector each spawn
	std::vector<ItemBase*>::iterator iterItems;
	std::vector<ItemBase*>::iterator iterGoals;
	for (iterGoals = goalItems.begin(); iterGoals != goalItems.end(); iterGoals++) {
		for (iterItems = spawnedItems.begin(); iterItems != spawnedItems.end(); iterItems++) {
			if ((*iterItems) == (*iterGoals)) {
				spawnedItems.erase(iterItems);
				break;
			}
		}	
		delete (*iterGoals);
	}
	goalItems.clear();

	GoalItem* goalItem = new GoalItem(theLevel, characterManager, renderer, input);
	Vector2D* goalLocation = theLevel->GetAGoalLocation();
	goalItem->Spawn((int)goalLocation->X, (int)goalLocation->Y);

	//first list is for update / drawing, second for easy finding
	spawnedItems.push_back(goalItem);
	goalItems.push_back(goalItem);
}