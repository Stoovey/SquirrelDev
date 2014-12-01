#include "InputManager.h"

InputManager::InputManager() {
	for (int i = 0; i < MAX_PADS; i++) {
		gamepads[i] = new X360Controller();	
	}

	keyboard = new Keyboard();
}

InputManager::~InputManager() {
	for (int i = 0; i < MAX_PADS; i++)
		delete gamepads[i];

	delete keyboard;
}

void InputManager::Update() {

	for (int i = 0; i < MAX_PADS; i++)
		if (gamepads[i]->GetIsActive())
			gamepads[i]->Update();

	keyboard->Update();
}

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

void InputManager::HandleKeyboardEvent(SDL_Event& keyboardEvent) {
	keyboard->HandleKeyboardEvent(keyboardEvent);
}

bool InputManager::IsPlayerPadActive(int playerID) {
	if (playerID >= 0 && playerID < MAX_PADS)
		return (gamepads[playerID]->GetIsActive());
	else
		return NULL;
}

int InputManager::WasPadButtonPressedByAnyPad(SDL_GameControllerButton button) {
	for (int i = 0; i < MAX_PADS; i++)
		if (WasPadButtonPressed(i, button))
			return i;

	return -1;
}

bool InputManager::WasPadButtonPressed(int playerIndex, SDL_GameControllerButton button) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->WasButtonPressed(button);
}

bool InputManager::WasPadButtonReleased(int playerIndex, SDL_GameControllerButton button) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->WasButtonReleased(button);
}

bool InputManager::IsPadButtonHeld(int playerIndex, SDL_GameControllerButton button) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->IsButtonHeld(button);
}

float InputManager::GetPadAxisValue(int playerIndex, SDL_GameControllerAxis axis) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->GetAxisValue(axis);
}

Vector2D InputManager::GetPadStickAsVec2D(int playerIndex, SDL_GameControllerButton stick) {
	if (playerIndex >= 0 && playerIndex < MAX_PADS)
		return gamepads[playerIndex]->GetStickVector(stick);
}

void InputManager::addGamepad(SDL_Event& padAddedEvent) {
	//the ID by which SDL refers to the new controller
	int padID = padAddedEvent.cdevice.which;
	
	//find an incactive entry in the gamepads array, store new pad there
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

void InputManager::HandlePadButtonEvent(SDL_Event& buttonEvent) {
	int playerPadIndex = sdlIDtoPlayerIndexMap[buttonEvent.cdevice.which];
	gamepads[playerPadIndex]->HandleButtonEvent(buttonEvent);
}

void InputManager::HandlePadAxisMotionEvent(SDL_Event& axisEvent) {
	int playerPadIndex = sdlIDtoPlayerIndexMap[axisEvent.caxis.which];
	gamepads[playerPadIndex]->HandleAxisEvent(axisEvent);
}

bool InputManager::IsKeyHeld(int key) {
	return keyboard->IsKeyHeld(key);
}
	
bool InputManager::WasKeyReleased(int key) {
	return keyboard->WasKeyReleased(key);
}

bool InputManager::WasKeyPressed(int key) {
	return keyboard->WasKeyPressed(key);
}