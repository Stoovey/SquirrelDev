#include "GamestateManager.h"
#include <iostream>

//delete any states
GamestateManager::~GamestateManager() {
	std::cout << "GamestateManager dtor called" << std::endl;
	//create an iterator, make it visit every element in the gamestates vector
	std::vector<GameState*>::iterator iter;
	for (iter = gameStates.begin(); iter != gameStates.end(); iter++) {
		//delete each one
		delete (*iter);
	}
}

//add a new state
void GamestateManager::AddState(GameState* state) {

	//add 'state' to the end of the gamestates vector
	gameStates.push_back(state);
}

//clear states vector
void GamestateManager::ChangeState(GameState* state) {
	
	//create an iterator, make it visit every element in the gamestates vector
	std::vector<GameState*>::iterator iter;
	for (iter = gameStates.begin(); iter != gameStates.end(); iter++) {
		//delete each one
		delete (*iter);
	}

	// empty the vector
	gameStates.clear();

	//add just the state we were passed
	AddState(state);
}

//remove 'top' state
void GamestateManager::RemoveTopState() {
	
	//delete last entry in the gamestates vector
	delete gameStates.back();

	//remove last entry from the vector
	gameStates.pop_back();
}

//update only the 'top' state, if this returns false, the game should quit
bool GamestateManager::Update(unsigned int deltaTime) {

	//update only the last entry in the gamestates vector
	return gameStates.back()->Update(deltaTime);
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