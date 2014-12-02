#ifndef _CHARACTERBASE_
#define _CHARACTERBASE_

#include <SDL.h>
#include "baseObjects.h"
#include "Vector2D.h"
#include "InputManager.h"

/* the player can be in any of these states
 * we can check which it is and do things
 * accordingly */
enum PlayerState {
	Spawning,
	Normal,
	Jumping,
	Falling,
	Dead
};

class CharacterBase : public baseObjects {

public:
	//constructor / destructor
	CharacterBase(InputManager* input);
	~CharacterBase();

	/* update and draw functions, 'virtual' means
	 * that any classes which inherit from this one
	 * can provide their own versions of these,
	 * the "=  0" means they MUST do */
	virtual void Update(unsigned int deltaTime) = 0;
	virtual void Draw(SDL_Renderer& renderer) = 0;

	/* called when this player has died, as with update and
	 * draw, the inheriting class MUST provide this */
	virtual void RespawnPlayer() = 0;

	//called to add this player to the game
	void Activate(int padID);

	//allow caller to see this players state, padID, score and wether it is active
	PlayerState GetState();
	int GetPadID() { return padID; }
	int GetScore() { return score; }
	bool GetIsActive() { return isActive; }
	
	//allow caller to set this players state and adjust its score
	void SetState(PlayerState state);
	void AdjustScore(int value);

protected:
	//hold this players current state
	PlayerState playerState;

	//allow player to use input
	InputManager* input;
	
	//where this player is in 2D
	Vector2D position;

	bool isActive;
	int padID;
	int score;
	float speed;
	float jumpVel;		//how fast jumping is
	float fallingVel;	//how fat falling is
	float jumpFallMoveSpeed;	//controls 'speed' while in the air
	float normalMoveSpeed;		//controls 'speed' normally
};

#endif