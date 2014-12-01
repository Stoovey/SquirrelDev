#include "GamestateManager.h"

//delete any states
GamestateManager::~GamestateManager() {
	std::vector<GameState*>::iterator iter;
	for (iter = gameStates.begin(); iter != gameStates.end(); iter++)
		delete (*iter);
}

//add a new state
void GamestateManager::AddState(GameState* state) {
	gameStates.push_back(state);
}

//clear states vector
void GamestateManager::RemoveAllStates() {
	gameStates.clear();
}

//remove 'top' state
void GamestateManager::RemoveTopState() {
	gameStates.pop_back();
}

//update only the 'top' state
void GamestateManager::Update(unsigned int deltaTime) {
	gameStates.back()->Update(deltaTime);
}

//draw every state
void GamestateManager::Draw(SDL_Renderer* renderer) {
	std::vector<GameState*>::iterator iter;
	for (iter = gameStates.begin(); iter != gameStates.end(); iter++)
		(*iter)->Draw(renderer);
}