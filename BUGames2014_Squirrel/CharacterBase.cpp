#include "CharacterBase.h"

CharacterBase::CharacterBase(InputManager* input) {
	this->input = input;
	this->isActive = false;
	this->score = 0;
}

CharacterBase::~CharacterBase() {

}

void CharacterBase::Update(unsigned int deltaTime) {

}

void CharacterBase::Draw(SDL_Renderer& renderer) {

}

void CharacterBase::SetState(PlayerState state) {
	playerState = state;
	if (state == PlayerState::Normal) {
		speed = normalMoveSpeed;
		fallingVel = 0.1f;
	}
	else if (state == PlayerState::Falling)
		speed = jumpFallMoveSpeed;
}

void CharacterBase::RespawnPlayer() {

}

PlayerState CharacterBase::GetState() {
	return playerState;
}

void CharacterBase::Activate(int padID) {
	this->padID = padID;
	this->isActive = true;
}

void CharacterBase::AdjustScore(int value) {
	score += value;
}