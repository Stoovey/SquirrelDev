#include "Keyboard.h"

//constructor
Keyboard::Keyboard() {
	BuildSDLKeyMap();
	
	/* see how many keys we are trackign the state of,
	 * build arrays with that many bool elements in */
	numKeyCodes = SDLKeyMap.size();
	currKeysState = new bool[numKeyCodes];
	prevKeysState = new bool[numKeyCodes];

	//set all array elements to false to start with
	for (int i = 0; i < numKeyCodes; i++) {
		currKeysState[i] = false;
		prevKeysState[i] = false;
	}
}

//destructor
Keyboard::~Keyboard() {
	delete[] currKeysState;
	delete[] prevKeysState;
}

void Keyboard::Update() {
	//copy values from 'current frame' keys array to 'previous frame'
	for (int i = 0; i < numKeyCodes; i++)
		prevKeysState[i] = currKeysState[i];
}

//handle all SDL keyboard events
void Keyboard::HandleKeyboardEvent(SDL_Event& keyboardEvent) {

	//find out which of our key array elements the incoming key maps to
	int keyArrayIndex = GetKeyIndexFromSDLKeyCode(keyboardEvent.key.keysym.sym);
	
	//if the key is one we are interested in...
	if (keyArrayIndex != -1) {

		//..store its current state
		if (keyboardEvent.type == SDL_KEYDOWN)
			currKeysState[keyArrayIndex] = true;
		else if (keyboardEvent.type == SDL_KEYUP)
			currKeysState[keyArrayIndex] = false;
	}
}

//return true if a given key is held, false if not
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

//return true if a given key was released, false if not
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

//return true if a given key was pressed, false if not
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
	//convert an SDL Key code into our own key arrays indices
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