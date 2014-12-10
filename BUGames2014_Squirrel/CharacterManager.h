#ifndef _CHARACTERMANAGER_
#define _CHARACTERMANAGER_

#include "Services.h"
#include "CharacterBase.h"
#include "TestCharacter.h"
#include "InputManager.h"
#include "CollisionHelper.h"
#include "Sprite.h"
#include <vector>

class CharacterManager : public ServiceBase {

public:
	//constructor / destructor
	CharacterManager(Services* services);
	~CharacterManager();

	//allow players to join or leave the game
	void AddPlayer(int padID);
	void RemovePlayer(int padID);

	//update and draw all active characters
	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* render);

	//returns the player list to the caller
	std::vector<CharacterBase*>& GetPlayers() { return players; }
	
	int location;
	std::vector<Sprite*> scoreUI;
	std::vector<Sprite*> numbersUI;

private:
	//contains the list of all four players
	std::vector<CharacterBase*> players;

	//allows access to player input
	InputManager* input;
};

#endif