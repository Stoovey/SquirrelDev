#ifndef gameManager_h
#define gameManager_h

#include<iostream>
#include"gameObject.h"
#include<vector>

class gameManager{
protected:
	//------------------List------------------//
	std::vector<gameObject*> playerList;
	std::vector<gameObject*> bulletList;
	std::vector<gameObject*> enemyList;
	std::vector<gameObject*> backgroundList;
	std::vector<gameObject*> powerUpList;
	//------------------List------------------//
	gameManager();

	static gameManager* pSharedGameManager;

public:
	static gameManager* sharedGameManager();

	void addToPlayerList(gameObject* tgo);
	void addToEnemyList(gameObject* tgo);
	void addToBulletList(gameObject* tgo);
	void addToBackgroundList(gameObject* tgo);
	void drawLists(SDL_Surface* screen);
	void processInputs(SDL_Event evt);
	void updateWorld(SDL_Surface* screen);
	void sweepList();
	bool collisionBetween(gameObject* tgo1, gameObject* tgo2);
	void checkAllCollisions();
};

#endif