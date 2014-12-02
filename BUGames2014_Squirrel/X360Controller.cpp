#include "X360Controller.h"

const float X360Controller::AXIS_DEADZONE = 0.25f;

X360Controller::X360Controller() {
	sdl_ID = -1;
	sdl_Controller = NULL;
	isActive = false;

	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++) {
		currentButtonStates[i] = false;
		prevButtonState[i] = false;
	}

	for (int i = 0; i < SDL_CONTROLLER_AXIS_MAX; i++) {
		axisStates[i] = 0.f;
	}
}

X360Controller::~X360Controller() {
	if (sdl_Controller)
		SDL_GameControllerClose(sdl_Controller);
}

bool X360Controller::Activate(int sdl_ID) {
	
	sdl_Controller = SDL_GameControllerOpen(sdl_ID);
	
	std::cout << "Added: " << SDL_GameControllerName(sdl_Controller) << std::endl;

	if (!sdl_Controller)	
		return false;

	sdl_ID = sdl_ID;
	isActive = true;
	return true;
}

void X360Controller::Deactivate() {
	if (sdl_Controller)
		SDL_GameControllerClose(sdl_Controller);

	sdl_ID = -1;
	isActive = false;
}

void X360Controller::Update() {
	for (int i = 0; i < SDL_CONTROLLER_BUTTON_MAX; i++)
		prevButtonState[i] = currentButtonStates[i];
}

void X360Controller::HandleButtonEvent(SDL_Event& buttonEvent) {
	//make sure we have a valid button ID for an X360 pad
	int buttonID = buttonEvent.cbutton.button;
	if (buttonID >= 0 && buttonID < SDL_CONTROLLER_BUTTON_MAX) {

		if (buttonEvent.cbutton.type == SDL_CONTROLLERBUTTONDOWN)
			currentButtonStates[buttonID] = true;
		else
			currentButtonStates[buttonID] = false;
	}
	SDL_CONTROLLER_BUTTON_A;
}

void X360Controller::HandleAxisEvent(SDL_Event& axisEvent) {
	//make sure we have a valid axis ID for an X360 pad
	int axisID = axisEvent.caxis.axis;
	if (axisID >= 0 && axisID < SDL_CONTROLLER_AXIS_MAX) {
		float normalisedAxisValue = (float)(axisEvent.caxis.value) / SHRT_MAX; 
		if (normalisedAxisValue > AXIS_DEADZONE || normalisedAxisValue < -AXIS_DEADZONE)
			axisStates[axisID] = normalisedAxisValue; 
		else
			axisStates[axisID] = 0;
	}
}

bool X360Controller::WasButtonPressed(SDL_GameControllerButton button) {
	//if a button was not down last frame but is now, then it was just pressed
	return (!prevButtonState[button] && currentButtonStates[button]);
}

bool X360Controller::WasButtonReleased(SDL_GameControllerButton button) {
	//if a button was down last frame but is not now, then it was just released
	return (prevButtonState[button] && !currentButtonStates[button]);
}

bool X360Controller::IsButtonHeld(SDL_GameControllerButton button) {
	//if a button was down last frame and still is, then it is held
	return (prevButtonState[button] && currentButtonStates[button]);
}

float X360Controller::GetAxisValue(SDL_GameControllerAxis axis) {
	return axisStates[axis];
}

Vector2D X360Controller::GetStickVector(SDL_GameControllerButton stick) {
	
	if (stick == SDL_CONTROLLER_BUTTON_LEFTSTICK)
		return Vector2D(axisStates[SDL_CONTROLLER_AXIS_LEFTX], 
						axisStates[SDL_CONTROLLER_AXIS_LEFTY]);
	else if (stick == SDL_CONTROLLER_BUTTON_RIGHTSTICK)
		return Vector2D(axisStates[SDL_CONTROLLER_AXIS_RIGHTX], 
						axisStates[SDL_CONTROLLER_AXIS_RIGHTY]);
	else
		return Vector2D();
}

//accessors
bool X360Controller::GetIsActive() { return isActive; }

int X360Controller::GetSDL_ID() { return sdl_ID; }