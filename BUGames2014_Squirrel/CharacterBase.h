#ifndef _CHARACTERBASE_
#define _CHARACTERBASE_

#include <SDL.h>
#include "baseObjects.h"
#include "Vector2D.h"
#include "InputManager.h"

enum PlayerState {
	Spawning,
	Normal,
	Jumping,
	Falling,
	Dead
};

class CharacterBase : public baseObjects {

public:
	CharacterBase(InputManager* input);
	~CharacterBase();

	virtual void Update(unsigned int deltaTime);
	virtual void Draw(SDL_Renderer& renderer);

	void SetState(PlayerState state);
	PlayerState GetState();
	void SetPlayerState(PlayerState ps) { playerState = ps; }
	virtual void RespawnPlayer();

	bool GetIsActive() { return isActive; }
	void Activate(int adID);

	int GetPadID() { return padID; }

	int GetScore() { return score; }
	void AdjustScore(int value);

protected:
	bool isActive;
	
	InputManager* input;
	float speed;
	
	int padID;

	int score;

	Vector2D position;
	Vector2D velocity;
	Vector2D acceleration;

	float maxAccel;
	float maxVelocity;

	//jumping / falling
	float jumpVel;
	float fallingVel;

	float jumpFallMoveSpeed;
	float normalMoveSpeed;

	PlayerState playerState;
};

#endif