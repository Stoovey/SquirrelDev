#include"gameManager.h"

gameManager::gameManager(){
	std::cout << "game manager loaded...";
}

//global static instance of gameManager class
gameManager* gameManager::pSharedGameManager = NULL;

/*------------------------------------------------------
sharedGameManager() returns single instance
of the gameManager class
------------------------------------------------------*/
gameManager* gameManager::sharedGameManager(){
	if (pSharedGameManager == NULL){
		pSharedGameManager = new gameManager();
	}
	return pSharedGameManager;
}

void gameManager::addToPlayerList(gameObject* tgo){
	playerList.push_back(tgo);
}

void gameManager::addToEnemyList(gameObject* tgo){
	enemyList.push_back(tgo);
}

void gameManager::addToBulletList(gameObject* tgo){
	bulletList.push_back(tgo);
}

void gameManager::addToBackgroundList(gameObject* tgo){
	backgroundList.push_back(tgo);
}

void gameManager::drawLists(SDL_Surface* screen){

	for (int i = 0; i<backgroundList.size(); i++){
		if (backgroundList.at(i)->getAlive() == true){
			backgroundList.at(i)->draw(screen);
		}
	}
	for (int i = 0; i<playerList.size(); i++){
		if (playerList.at(i)->getAlive() == true){
			playerList.at(i)->draw(screen);
		}
	}
	for (int i = 0; i<enemyList.size(); i++){
		if (enemyList.at(i)->getAlive() == true){
			enemyList.at(i)->draw(screen);
		}
	}
	for (int i = 0; i<bulletList.size(); i++){
		if (bulletList.at(i)->getAlive() == true){
			bulletList.at(i)->draw(screen);
		}
	}
	
}

void gameManager::processInputs(SDL_Event evt){
	for (int i = 0; i<playerList.size(); i++){
		if (playerList.at(i)->getActive() == true){
			playerList.at(i)->handleInput(evt);
		}
	}
	for (int i = 0; i<enemyList.size(); i++){
		if (enemyList.at(i)->getActive() == true){
			enemyList.at(i)->handleInput(evt);
		}
	}
}

void gameManager::updateWorld(SDL_Surface* screen){
	for (int i = 0; i<playerList.size(); i++){
		if (playerList.at(i)->getAlive() == true){
			playerList.at(i)->update(screen);
		}
	}
	for (int i = 0; i<enemyList.size(); i++){
		if (enemyList.at(i)->getAlive() == true){
			enemyList.at(i)->update(screen);
		}
	}
	for (int i = 0; i<bulletList.size(); i++){
		if (bulletList.at(i)->getAlive() == true){
			bulletList.at(i)->update(screen);
		}
	}
	for (int i = 0; i<backgroundList.size(); i++){
		if (backgroundList.at(i)->getAlive() == true){
			backgroundList.at(i)->update(screen);
		}
	}
	checkAllCollisions();
}

void gameManager::sweepList(){
	for (int i = 0; i<playerList.size(); i++){
		if (playerList.at(i)->getAlive() == false && playerList.at(i)->getActive() == false){
			delete playerList.at(i);
			playerList.erase(playerList.begin() + i);
		}
	}
	for (int i = 0; i<enemyList.size(); i++){
		if (enemyList.at(i)->getAlive() == false && enemyList.at(i)->getActive() == false){
			delete enemyList.at(i);
			enemyList.erase(enemyList.begin() + i);
		}
	}
	for (int i = 0; i<bulletList.size(); i++){
		if (bulletList.at(i)->getAlive() == false && bulletList.at(i)->getActive() == false){
			delete bulletList.at(i);
			bulletList.erase(bulletList.begin() + i);
		}
	}
	for (int i = 0; i<backgroundList.size(); i++){
		if (backgroundList.at(i)->getAlive() == false && backgroundList.at(i)->getActive() == false){
			delete backgroundList.at(i);
			backgroundList.erase(backgroundList.begin() + i);
		}
	}
}

bool gameManager::collisionBetween(gameObject* tgo1, gameObject* tgo2){
	if( (tgo1->getX() >= tgo2->getX() && tgo1->getX() <= (tgo2->getX() + tgo2->getW())) ||	((tgo1->getX() + tgo1->getW()) >= tgo2->getX() && (tgo1->getX() + tgo1->getW()) <= (tgo2->getX() + tgo2->getW())) ){
	//if((tgo1->getX()>=tgo2->getX()) && ((tgo1->getX() + tgo1->getW()) <= (tgo2->getX() + tgo2->getW()))){
		if ((tgo1->getY()) > tgo2->getY() && (tgo1->getY() < tgo2->getY() + tgo2->getH())){
			return true;
		}
	}
	return false;
}

void gameManager::checkAllCollisions(){
	for (int i = 0; i<bulletList.size(); i++){
		for (int j = 0; j<enemyList.size(); j++){
			if (collisionBetween(bulletList.at(i), enemyList.at(j)) == true){

				bulletList.at(i)->setAlive(false);
				bulletList.at(i)->setActive(false);

				enemyList.at(j)->setAlive(false);
				enemyList.at(j)->setActive(false);
			}
		}
	}
	
	for (int f = 0; f<playerList.size(); f++){
		for (int c = 0; c<enemyList.size(); c++){
			if (collisionBetween(playerList.at(f), enemyList.at(c)) == true){

				playerList.at(f)->setAlive(false);
				playerList.at(f)->setActive(false);
				
				enemyList.at(c)->setAlive(false);
				enemyList.at(c)->setActive(false);

				std::cout<<"collision player and enemy";
			}
		}
	}
}