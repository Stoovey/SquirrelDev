#pragma once

#include <iostream>
#include <unordered_map>
#include <sdl.h>

class Keyboard {

public:
	//constructor / destructor
	Keyboard();
	~Keyboard();

	void Update();

	//handle all SDL keyboard events
	void HandleKeyboardEvent(SDL_Event& keyboardEvent);
	
	//return info about keys
	bool IsKeyHeld(int key);
	bool WasKeyReleased( int key);
	bool WasKeyPressed(int key);

private:
	/* we don't need to track the whole keyboard
	 * just a given number of keys that we are
	 * interested in. */
	int numKeyCodes;

	//state of keys on this frame and last
	bool* currKeysState;
	bool* prevKeysState;

	/* SDL gives each key an enum keycode (like SDLK_A, SDLK_SPACE),
	 * we store the states of the ones we are interested in inside 
	 * the above bool* dynamic arrays. To do this we map SDLs
	 * keycodes onto our own array indices */

	//mapping of SDL keycodes to our key arrays indices
	std::unordered_map<int, int> SDLKeyMap;
	void BuildSDLKeyMap();
	int GetKeyIndexFromSDLKeyCode(int code);
};