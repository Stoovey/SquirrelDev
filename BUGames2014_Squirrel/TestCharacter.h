#ifndef _TESTCHARACTER_
#define _TESTCHARACTER_

#include "CharacterBase.h"
#include "Sprite.h"
#include <cmath>
#include <string>

//inherit from the 'CharacterBase' class
class TestCharacter : public CharacterBase {

public:
	//constructor / destructor
	TestCharacter(std::string spriteFileName, SDL_Renderer& renderer, InputManager* input);
	~TestCharacter();

	//update function, and specific ones to be used per state
	void Update(unsigned int deltaTime);
	void UpdateNormal(unsigned int deltaTime);
	void UpdateJumping(unsigned int deltaTime);
	void UpdateFalling(unsigned int deltaTime);

	//render this character
	void Draw(SDL_Renderer& renderer);
	
	//call when dead to respawn
	void RespawnPlayer();

private:
	//sprite this player is using
	Sprite* sprite;

	//check if we have gone offscreen
	void CheckInBounds();
	
	//update our position based on input
	void DoMove(unsigned int deltaTime);
};

#endif