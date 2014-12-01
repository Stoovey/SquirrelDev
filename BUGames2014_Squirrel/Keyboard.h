#pragma once

#include <iostream>
#include <unordered_map>
#include <sdl.h>

class Keyboard {

public:
	Keyboard();
	~Keyboard();

	void Update();

	void HandleKeyboardEvent(SDL_Event& keyboardEvent);
	bool IsKeyHeld(int key);
	bool WasKeyReleased( int key);
	bool WasKeyPressed(int key);

private:
	int numKeyCodes;
	bool* currKeysState;
	bool* prevKeysState;

	//contains mapping of SDL keycodes to our key arrays indices
	std::unordered_map<int, int> SDLKeyMap;
	
	void BuildSDLKeyMap();
	int GetKeyIndexFromSDLKeyCode(int code);
};