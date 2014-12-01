#include "TestCharacter.h"

TestCharacter::TestCharacter(std::string spriteFileName, SDL_Renderer& renderer, InputManager* input)
 : CharacterBase(input) {

	playerState = PlayerState::Falling;

	//create and load sprite
	sprite = new Sprite(spriteFileName, 0, 0, 64, 64, renderer);

	position.X = 600;
	position.Y = 130;

	normalMoveSpeed = .8f;
	jumpFallMoveSpeed = .4f;
	fallingVel = 0.2f;
	speed = normalMoveSpeed;

	setW(64);
	setH(64);
}

TestCharacter::~TestCharacter() {
	delete sprite;
}

void TestCharacter::DoMove(unsigned int deltaTime) {
	//get acceleration from left stick
	float leftStickX = input->GetPadAxisValue(padID, SDL_CONTROLLER_AXIS_LEFTX);
	if (abs(leftStickX) > 0.2f)
		position.X += (leftStickX * speed) * deltaTime;
	else {
		//keyboard controls hack
		if (input->IsKeyHeld(SDLK_LEFT))
			leftStickX = -1;
		else if (input->IsKeyHeld(SDLK_RIGHT))
			leftStickX = 1; 

		position.X += (leftStickX * speed) * deltaTime;
	}

	setX(position.X);
}

void TestCharacter::OLD_DoMove(unsigned int deltaTime) {
	//get acceleration from left stick
	float leftStickX = input->GetPadAxisValue(padID, SDL_CONTROLLER_AXIS_LEFTX);
	
	//add on to accel, or reduce it if player not moving
	if (abs(leftStickX) > 0.2f) 
		acceleration.X += (leftStickX * speed) * deltaTime;
	else
		acceleration.X *= 0.99f;

	//keep accel within bounds
	if (acceleration.X >  maxAccel) acceleration.X =  maxAccel;
	if (acceleration.X < -maxAccel) acceleration.X = -maxAccel;

	//adjust velocity
	//add on to accel, or reduce it if player not moving
	if (abs(leftStickX) > 0.2f) 
		velocity.X += acceleration.X * deltaTime;
	else
		velocity.X *= 0.99f;
	

	//keep velocity within bounds
	if (velocity.X >  maxVelocity) velocity.X =  maxVelocity;
	if (velocity.X < -maxVelocity) velocity.X = -maxVelocity;

	position.X += velocity.X * deltaTime;
}

void TestCharacter::CheckInBounds() {
	if (position.X < -sprite->GetWidth() || position.X > 1280 || position.Y > 700) {
		if (score > 0) score--;
		playerState = PlayerState::Dead;
	}
}

void TestCharacter::RespawnPlayer() {
	position.X = 600;
	position.Y = 400;
	playerState = PlayerState::Falling;
}

void TestCharacter::Update(unsigned int deltaTime) {

	CheckInBounds();

	if (playerState == PlayerState::Normal)
		UpdateNormal(deltaTime);
	else if (playerState == PlayerState::Jumping)
		UpdateJumping(deltaTime);
	else if (playerState == PlayerState::Falling)
		UpdateFalling(deltaTime);
}

void TestCharacter::UpdateNormal(unsigned int deltaTime) {
	if (input->WasPadButtonPressed(padID, SDL_CONTROLLER_BUTTON_A) ||
		input->WasKeyPressed(SDLK_SPACE)) {
		speed = jumpFallMoveSpeed;
		jumpVel = 1;
		playerState = PlayerState::Jumping;
	}

	DoMove(deltaTime);
}

void TestCharacter::UpdateJumping(unsigned int deltaTime) {
	DoMove(deltaTime);
	
	position.Y -= jumpVel * deltaTime;
	jumpVel -= (0.004 * jumpVel) * deltaTime;
	setY(position.Y);

	if (jumpVel < 0.1f) {
		fallingVel = 0.1f;
		playerState = PlayerState::Falling;
	}
}

void TestCharacter::UpdateFalling(unsigned int deltaTime) {
	DoMove(deltaTime);
	
	position.Y += fallingVel * deltaTime;
	fallingVel += (0.005 * fallingVel) * deltaTime;
	setY(position.Y);
}

void TestCharacter::Draw(SDL_Renderer& renderer) {
	sprite->Draw(position.X, position.Y, sprite->GetWidth(), sprite->GetHeight(), renderer);
}