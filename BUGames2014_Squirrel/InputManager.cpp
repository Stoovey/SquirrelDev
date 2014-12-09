#include "InputManager.h"

//constructor
InputManager::InputManager() {
	for (int i = 0; i < MAX_PADS; i++) {
		gamepads[i] = new X360Controller();	
	}

	keyboard = new Keyboard();
}

//destructor
InputManager::~InputManager() {
	for (int i = 0; i < MAX_PADS; i++)
		delete gamepads[i];

	delete keyboard;
}

/* update all our input devices, this gets them
 * ready for the next frame */
void InputManager::Update() {
	//update all pads
	for (int i = 0; i < MAX_PADS; i++)
		if (gamepads[i]->GetIsActive())
			gamepads[i]->Update();

	//same for KB
	keyboard->Update();
}

/* SDL sends all input related events here and then we farm
 * them off to different functions depending on what they are */
void InputManager::HandleGamepadEvent(SDL_Event& gamepadEvent) {

	switch (gamepadEvent.type) {
		case SDL_CONTROLLERAXISMOTION:
			HandlePadAxisMotionEvent(gamepadEvent);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
		case SDL_CONTROLLERBUTTONUP:
			HandlePadButtonEvent(gamepadEvent);
			break;
		case SDL_CONTROLLERDEVICEADDED:
			addGamepad(gamepadEvent);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			removeGamepad(gamepadEvent);
			break;
	}
}

//send all keyboard events to our keyboard object
void InputManager::HandleKeyboardEvent(SDL_Event& keyboardEvent) {
	keyboard->HandleKeyboardEvent(keyboardEvent);
}

//check if a given players pad is working
bool InputManager::IsPlayerPadActive(int playerID) {
	if (playerID >= 0 && playerID < MAX_PADS)
		return (gamepads[playerID]->GetIsActive());
	else
		return NULL;
}

/* if any pad has pressed the requested button the return its padID,
 * return -1 if no pad has pressed it */
int InputManager::WasPadButtonPressedByAnyPad(SDL_GameControllerButton button) {
	for (int i = 0; i < MAX_PADS; i++)
		if (WasPadButtonPressed(i, button))
			return i;

	return -1;
}

//true if a specific pad has pressed a specific button, false if not
bool InputManager::WasPadButtonPressed(int playerIndex, SDL_GameControllerButton button) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->WasButtonPressed(button);

	return false;
}

//true if a specific pad has released a specific button, false if not
bool InputManager::WasPadButtonReleased(int playerIndex, SDL_GameControllerButton button) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->WasButtonReleased(button);

	return false;
}

//true if a specific pad is holding down a specific button, false if not
bool InputManager::IsPadButtonHeld(int playerIndex, SDL_GameControllerButton button) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->IsButtonHeld(button);

	return false;
}

//get current value of a given axis on a given pad
float InputManager::GetPadAxisValue(int playerIndex, SDL_GameControllerAxis axis) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->GetAxisValue(axis);

	return false;
}

//get a current vec2 representation of a given stick on a given pad
Vector2D InputManager::GetPadStickAsVec2D(int playerIndex, SDL_GameControllerButton stick) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->GetStickVector(stick);

	return Vector2D();
}

//add a new pad to the manager
void InputManager::addGamepad(SDL_Event& padAddedEvent) {
	//the ID by which SDL refers to the new controller
	int padID = padAddedEvent.cdevice.which;
	
	//find an inactive entry in the gamepads array, store new pad there
	for (int i = 0; i < MAX_PADS; i++) {
		if (!gamepads[i]->GetIsActive()) {
			if (gamepads[i]->Activate(padID)) {
				sdlIDtoPlayerIndexMap[padID] = i;
				std::cout << "Registered pad " << padID << " as player " << i << std::endl;
				return;
			}
		}
	}
	
	std::cout << "Gamepads array has no inactive elements, failed to store inserted controller" << std::endl;
}

/**
 * This seems to only get called when a controller that was
 * plugged in at program launch is removed.
 */
void InputManager::removeGamepad(SDL_Event& padRemovedEvent) {
	int playerPadID = sdlIDtoPlayerIndexMap[padRemovedEvent.cdevice.which];
	gamepads[playerPadID]->Deactivate();
}

//handle SDL events to do with pad buttons
void InputManager::HandlePadButtonEvent(SDL_Event& buttonEvent) {
	int playerPadIndex = sdlIDtoPlayerIndexMap[buttonEvent.cdevice.which];
	gamepads[playerPadIndex]->HandleButtonEvent(buttonEvent);
}

//handle SDL events to do with pad axes
void InputManager::HandlePadAxisMotionEvent(SDL_Event& axisEvent) {
	int playerPadIndex = sdlIDtoPlayerIndexMap[axisEvent.caxis.which];
	gamepads[playerPadIndex]->HandleAxisEvent(axisEvent);
}

//return true if a given key is held down
bool InputManager::IsKeyHeld(int key) {
	return keyboard->IsKeyHeld(key);
}

//return true if a given key was released
bool InputManager::WasKeyReleased(int key) {
	return keyboard->WasKeyReleased(key);
}

//return true if a given key was pressed
bool InputManager::WasKeyPressed(int key) {
	return keyboard->WasKeyPressed(key);
}