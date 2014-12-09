#include "TestCharacter.h"

//constructor
TestCharacter::TestCharacter(std::string spriteFileName, SDL_Renderer& renderer, InputManager* input)
 : CharacterBase(input) {
	//start in the falling state
	playerState = PlayerState::Falling;

	//create and load sprite
	sprite = new Sprite(spriteFileName, 0, 0, 64, 64, renderer);

	//initial position
	position.X = 600;
	position.Y = 130;

	//how fast we can move
	normalMoveSpeed = .8f;
	jumpFallMoveSpeed = .4f;
	fallingVel = 0.2f;
	speed = normalMoveSpeed;

	//store desired sprite width away
	setW(64);
	setH(64);
}

//destructor
TestCharacter::~TestCharacter() {
	delete sprite;
}

//allow player to move based on input
void TestCharacter::DoMove(unsigned int deltaTime) {
	//read this players left stick X position
	float leftStickX = input->GetPadAxisValue(padID, SDL_CONTROLLER_AXIS_LEFTX);
	
	//if left stick was bein g used
	if (abs(leftStickX) > 0.f)
		//scale stickX amouny by player speed and deltaTime
		position.X += (leftStickX * speed) * deltaTime;
	else {
		//if no pad then use this hacky keyboard controls code
		if (input->IsKeyHeld(SDLK_LEFT))
			leftStickX = -1;
		else if (input->IsKeyHeld(SDLK_RIGHT))
			leftStickX = 1; 

		position.X += (leftStickX * speed) * deltaTime;
	}

	//store our new position
	setX(position.X);
}

//check if we have gone offscreen, set to dead state if we have
void TestCharacter::CheckInBounds() {
	if (position.X < -sprite->GetWidth() || position.X > 1280 || position.Y > 700) {
		if (score > 0) score--;
		playerState = PlayerState::Dead;
	}
}

//reset X/Y pos and put in falling state
void TestCharacter::RespawnPlayer() {
	position.X = 600;
	position.Y = 400;
	playerState = PlayerState::Falling;
}

//update this character
void TestCharacter::Update(unsigned int deltaTime) {
	//see if we are onscreen (kills if not)
	CheckInBounds();

	//call the correct update function, depending on our state
	if (playerState == PlayerState::Normal)
		UpdateNormal(deltaTime);
	else if (playerState == PlayerState::Jumping)
		UpdateJumping(deltaTime);
	else if (playerState == PlayerState::Falling)
		UpdateFalling(deltaTime);
}

//update function to use if player in normal state
void TestCharacter::UpdateNormal(unsigned int deltaTime) {
	//check if button A was pressed on this player pad, or space on the keyboard
	if (input->WasPadButtonPressed(padID, SDL_CONTROLLER_BUTTON_A) || input->WasKeyPressed(SDLK_SPACE)) {
		//if yes, then change movement speeds and set to jumping state
		speed = jumpFallMoveSpeed;
		jumpVel = 1;
		playerState = PlayerState::Jumping;
	}

	//allow player to move based on input
	DoMove(deltaTime);
}

//update funtion to use if player in jumping state
void TestCharacter::UpdateJumping(unsigned int deltaTime) {
	//allow player to move based on input
	DoMove(deltaTime);
	
	//move up a bit 
	position.Y -= jumpVel * deltaTime;
	setY(position.Y);

	//slow rate of ascent a bit for next frame
	jumpVel -= (0.004f * jumpVel) * deltaTime;
	
	//if ascent has slowed down to not much...
	if (jumpVel < 0.1f) {
		//set falling speed and go to falling state
		fallingVel = 0.1f;
		playerState = PlayerState::Falling;
	}
}

//update function to use if player in falling state
void TestCharacter::UpdateFalling(unsigned int deltaTime) {
	//allow player to move based on input
	DoMove(deltaTime);
	
	//move down a bit
	position.Y += fallingVel * deltaTime;
	setY(position.Y);

	//increase fall speed for next frame
	fallingVel += (0.005f * fallingVel) * deltaTime;
}

//draw this characters sprite
void TestCharacter::Draw(SDL_Renderer& renderer) {
	sprite->Draw((int)position.X, (int)position.Y, sprite->GetWidth(), sprite->GetHeight(), renderer);
}