#pragma once

#include <SDL.h>
#include <iostream>
#include <unordered_map>
#include "Vector2D.h"
#include "X360Controller.h"
#include "Keyboard.h"

class InputManager {

public:
	InputManager();
	~InputManager();

	void Update();

	bool IsPlayerPadActive(int playerID);

	//InputManager handles input events vis these functions
	void HandleGamepadEvent(SDL_Event& gamepadEvent);
	void HandleKeyboardEvent(SDL_Event& keyboardEvent);

	//InputManager exposes gamepads via these functions:
	bool WasPadButtonPressed(int playerIndex, SDL_GameControllerButton button);
	bool WasPadButtonReleased(int playerIndex, SDL_GameControllerButton button);
	bool IsPadButtonHeld(int playerIndex, SDL_GameControllerButton button);
	float GetPadAxisValue(int playerIndex, SDL_GameControllerAxis axis);
	Vector2D GetPadStickAsVec2D(int playerIndex, SDL_GameControllerButton stick);

	//return padID of first pad found to have pressed, or -1 if none have
	int WasPadButtonPressedByAnyPad(SDL_GameControllerButton button);
	
	//expose keyboard via these functions
	bool IsKeyHeld(int key);
	bool WasKeyReleased(int key);
	bool WasKeyPressed(int key);

private:
	
	//support four players using pads
	static const int MAX_PADS = 4;
	X360Controller* gamepads[MAX_PADS];
	std::unordered_map<int, int> sdlIDtoPlayerIndexMap;

	//handle gamepad events
	void HandlePadButtonEvent(SDL_Event& buttonEvent);
	void HandlePadAxisMotionEvent(SDL_Event& axisEvent);

	//gamepad hotplugging
	void addGamepad(SDL_Event& padAddedEvent);
	void removeGamepad(SDL_Event& padRemovedEvent);

	//keyboard
	Keyboard* keyboard;
};