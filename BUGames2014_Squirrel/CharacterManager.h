#ifndef _CHARACTERMANAGER_
#define _CHARACTERMANAGER_

#include "CharacterBase.h"
#include "TestCharacter.h"
#include "InputManager.h"
#include "Collision.h"
#include "Sprite.h"
#include <vector>

class CharacterManager {

public:
	CharacterManager(SDL_Renderer* render, InputManager* input);
	~CharacterManager();

	void AddPlayer(int padID);
	void RemovePlayer(int padID);

	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* render);

	std::vector<CharacterBase*>& GetPlayers() { return players; }
	int location;
	std::vector<Sprite*> scoreUI;
	std::vector<Sprite*> numbersUI;

private:
	std::vector<CharacterBase*> players;
	InputManager* input;
};

#endif