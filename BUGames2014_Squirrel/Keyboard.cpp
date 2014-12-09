#include "Keyboard.h"

Keyboard::Keyboard() {
	BuildSDLKeyMap();
	numKeyCodes = SDLKeyMap.size();
	currKeysState = new bool[numKeyCodes];
	prevKeysState = new bool[numKeyCodes];

	for (int i = 0; i < numKeyCodes; i++) {
		currKeysState[i] = false;
		prevKeysState[i] = false;
	}
}

Keyboard::~Keyboard() {
	delete[] currKeysState;
	delete[] prevKeysState;
}

void Keyboard::Update() {
	//copy values from 'current frame' keys array to 'previous frame'
	for (int i = 0; i < numKeyCodes; i++)
		prevKeysState[i] = currKeysState[i];
}

void Keyboard::HandleKeyboardEvent(SDL_Event& keyboardEvent) {
	std::unordered_map<int, int>::const_iterator iter = SDLKeyMap.find(keyboardEvent.key.keysym.sym);
	if (iter != SDLKeyMap.end()) {
		int keyArrayIndex = iter->second;

		if (keyboardEvent.type == SDL_KEYDOWN)
			currKeysState[keyArrayIndex] = true;
		else if (keyboardEvent.type == SDL_KEYUP)
			currKeysState[keyArrayIndex] = false;
	}
}

bool Keyboard::IsKeyHeld(int key) {
	int keyArrayIndex = GetKeyIndexFromSDLKeyCode(key);
	if (keyArrayIndex != -1) {

		//if a key is down this frame and was down last then it was held
		if (currKeysState[keyArrayIndex] && prevKeysState[keyArrayIndex])
			return true;
		else
			return false;
	}

	return false;
}

bool Keyboard::WasKeyReleased(int key) {
	int keyArrayIndex = GetKeyIndexFromSDLKeyCode(key);
	if (keyArrayIndex != -1) {

		//if a key is up this frame but was down last then it was pressed
		if (!currKeysState[keyArrayIndex] && prevKeysState[keyArrayIndex])
			return true;
		else
			return false;
	}

	return false;
}

bool Keyboard::WasKeyPressed(int key) {
	int keyArrayIndex = GetKeyIndexFromSDLKeyCode(key);
	if (keyArrayIndex != -1) {

		//if a key is down this frame but up last then it was pressed
		if (currKeysState[keyArrayIndex] && !prevKeysState[keyArrayIndex])
			return true;
		else
			return false;
	}

	return false;
}

int Keyboard::GetKeyIndexFromSDLKeyCode(int code) {
	//convert an SDL Key code into our own key arrays index
	std::unordered_map<int, int>::const_iterator iter = SDLKeyMap.find(code);
	if (iter != SDLKeyMap.end())
		return iter->second;
	else
		return -1;
}

void Keyboard::BuildSDLKeyMap() {
	//map SDLs keycodes to our key arays indices
	SDLKeyMap[SDLK_UP]     = 0;
	SDLKeyMap[SDLK_DOWN]   = 1;
	SDLKeyMap[SDLK_LEFT]   = 2;
	SDLKeyMap[SDLK_RIGHT]  = 3;
	SDLKeyMap[SDLK_ESCAPE] = 4;
	SDLKeyMap[SDLK_SPACE]  = 5;
	SDLKeyMap[SDLK_RETURN] = 6;
}