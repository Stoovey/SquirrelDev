#ifndef _TESTCHARACTER_
#define _TESTCHARACTER_

#include "CharacterBase.h"
#include "Sprite.h"
#include <cmath>
#include <string>

class TestCharacter : public CharacterBase {

public:
	TestCharacter(std::string spriteFileName, SDL_Renderer& renderer, InputManager* input);
	~TestCharacter();

	void Update(unsigned int deltaTime);
	void UpdateNormal(unsigned int deltaTime);
	void UpdateJumping(unsigned int deltaTime);
	void UpdateFalling(unsigned int deltaTime);

	void Draw(SDL_Renderer& renderer);
	void TestCharacter::RespawnPlayer();

private:
	Sprite* sprite;

	void CheckInBounds();
	
	void OLD_DoMove(unsigned int deltaTime);
	void DoMove(unsigned int deltaTime);
};

#endif