#include "GamestateManager.h"

//delete any states
GamestateManager::~GamestateManager() {
	//this deletes and removes all states
	RemoveAllStates();
}

//add a new state
void GamestateManager::AddState(GameState* state) {

	//add 'state' to the end of the gamestates vector
	gameStates.push_back(state);
}

//clear states vector
void GamestateManager::RemoveAllStates() {

	/* empty the vector, this does not delete the 
	 * objects being pointed to in it though */
	gameStates.clear();
}

//remove 'top' state
void GamestateManager::RemoveTopState() {
	
	//delete last entry in the gamestates vector
	delete gameStates.back();

	//remove last entry from the vector
	gameStates.pop_back();
}

//update only the 'top' state
void GamestateManager::Update(unsigned int deltaTime) {

	//update only the last entry in the gamestates vector
	gameStates.back()->Update(deltaTime);
}

//draw every gamestate which is in use
void GamestateManager::Draw(SDL_Renderer* renderer) {
	
	//create an iterator, make it visit every element in the gamestates vector
	std::vector<GameState*>::iterator iter;
	for (iter = gameStates.begin(); iter != gameStates.end(); iter++) {
		
		//call draw on the element which 'iter' is currently at
		(*iter)->Draw(renderer);
	}
}