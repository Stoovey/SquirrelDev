#include <SDL.h>
#include <iostream>
#include <string>
#include "TestCharacter.h"
#include "MenuState.h"
#include "Services.h"
#include "GamestateManager.h"
#include "Config.h"

int main(int argc, char *argv[])
{
	// Initialise
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		std::cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}

	int winPosX = 400;
	int winPosY = 200;
	int winWidth = 1280;
	int winHeight = 720;
	SDL_Window *window = SDL_CreateWindow("Alpha build -> Heterdox Games", winPosX, winPosY, winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

	//main services container
	Services* services = new Services(renderer);

	//store away some window details
	Config* config = (Config*)services->GetService(Service::Config);
	config->SetWinWidth(winWidth);
	config->SetWinHeight(winHeight);

	//Handles all input
	InputManager* inputManager = (InputManager*)services->GetService(Service::InputManager);

	//gameState handling
	GamestateManager* gamestateManager = (GamestateManager*)services->GetService(Service::GameStateManager);
	GameState* menuState = new MenuState(services);
	gamestateManager->AddState(menuState);

	//timing values so everything works the same
	//at any framerate
	unsigned int lastTime = SDL_GetTicks();
	unsigned int currentTime = 0;
	int deltaTime = 0;

	//main game loop
	bool go = true;
	while( go )
	{
		//work out our timing values
		currentTime = SDL_GetTicks();
		deltaTime = currentTime - lastTime;

		inputManager->Update();

		//event handling loop
		SDL_Event incomingEvent;
		while( SDL_PollEvent( &incomingEvent ) )
		{
			switch( incomingEvent.type )
			{
			case SDL_CONTROLLERAXISMOTION:
			case SDL_CONTROLLERBUTTONDOWN:
			case SDL_CONTROLLERBUTTONUP:
			case SDL_CONTROLLERDEVICEADDED:
			case SDL_CONTROLLERDEVICEREMOVED:
				inputManager->HandleGamepadEvent(incomingEvent);
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				inputManager->HandleKeyboardEvent(incomingEvent);
				break;

			case SDL_QUIT:
				go = false;
				break;
			}
		}

		//SDL_Quit may have occured above
		if (!go) break;
		
		//update state system
		go = gamestateManager->Update(deltaTime);

		// Draw stuff
		// Start by clearing what was drawn before
		SDL_SetRenderDrawColor( renderer, 0x0, 0x0, 0x0, 0xFF );
		SDL_RenderClear(renderer);

		//draw
		gamestateManager->Draw(renderer);

		SDL_RenderPresent(renderer);

		//store current frames time as last time
		lastTime = currentTime;
	}

	delete services;

	// If we get outside the main game loop, it means our user has requested we exit
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}