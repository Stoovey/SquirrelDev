#include "CharacterBase.h"

//constructor
CharacterBase::CharacterBase(InputManager* input) {
	this->input = input;
	this->isActive = false;
	this->score = 0;
}

//destructor
CharacterBase::~CharacterBase() {

}

//call to change this players state
void CharacterBase::SetState(PlayerState state) {
	//set our state to whatever the incoming state is
	playerState = state;

	//we may need to alter our speed, depending on what the new state is
	if (state == PlayerState::Normal) {
		speed = normalMoveSpeed;
		fallingVel = 0.1f;
	}
	else if (state == PlayerState::Falling)
		speed = jumpFallMoveSpeed;
}

//return this player state to the caller
PlayerState CharacterBase::GetState() {
	return playerState;
}

//store incoming padID, set isActive to true
void CharacterBase::Activate(int padID) {
	this->padID = padID;
	this->isActive = true;
}

//alter score by whatever value is passed in
void CharacterBase::AdjustScore(int value) {
	score += value;
}