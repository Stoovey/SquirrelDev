#pragma once

#include <SDL.h>
#include <iostream>
#include "Vector2D.h"

class X360Controller {

public:
	X360Controller();
	~X360Controller();

	bool Activate(int sdl_ID);
	void Deactivate();

	void Update();

	void HandleButtonEvent(SDL_Event& buttonEvent);
	void HandleAxisEvent(SDL_Event& axisEvent);

	//button / axix state functions
	bool WasButtonPressed(SDL_GameControllerButton button);
	bool WasButtonReleased(SDL_GameControllerButton button);
	bool IsButtonHeld(SDL_GameControllerButton button);
	float GetAxisValue(SDL_GameControllerAxis axis);
	Vector2D GetStickVector(SDL_GameControllerButton stick);
	static const float AXIS_DEADZONE;

	//accessors
	bool GetIsActive();
	int GetSDL_ID();

private:

	SDL_GameController* sdl_Controller;
	int sdl_ID;
	bool isActive;

	//button and axis states
	bool currentButtonStates[SDL_CONTROLLER_BUTTON_MAX];
	bool prevButtonState[SDL_CONTROLLER_BUTTON_MAX];
	float axisStates[SDL_CONTROLLER_AXIS_MAX];
};