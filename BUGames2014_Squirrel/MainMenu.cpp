// This is the main SDL include file
#include <SDL.h>
// iostream is so we can output error messages to console
#include <iostream>
#include "InputManager.h"
#include "ScollingBackground.h"
#include "menu.h"



void UpdatePlaying(SDL_Renderer &renderer);
void PlayCredits(SDL_Renderer &renderer);


using namespace std;

int main(int argc, char *argv[])
{
	// Initialise
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_GAMECONTROLLER ) < 0 )
	{
		cout << "Whoops! Something went very wrong, cannot initialise SDL :(" << std::endl;
		return -1;
	}

	int winPosX = 400;
	int winPosY = 200;
	int winWidth = 1368;
	int winHeight = 720;
	SDL_Window *window = SDL_CreateWindow("Game Window", winPosX, winPosY,	winWidth, winHeight,
		SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);

	SDL_Renderer * renderer = SDL_CreateRenderer(window, -1, 0);

	//Handles all input
	InputManager inputManager = InputManager();

	//menu
	Sprite* background = new Sprite("images/bkg/menuBkg.jpg", renderer);
	Menu* menu = new Menu(renderer, &inputManager);
	enum gameState {MENU, INGAME,CREDITS};
	gameState state = MENU; 

	// Ok, hopefully finished with initialisation now
	// Let's go and draw something!

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

		/* this needs doing before the event handling 'while' because
		 * this function updates our 'previous frame' pad data, and
		 * the event handling may overwrite some of the data we need
		 * to do that with */
		inputManager.Update();

		//check if we are quitting
		if (inputManager.IsKeyHeld(SDLK_ESCAPE) ||
			inputManager.IsPadButtonHeld(0, SDL_CONTROLLER_BUTTON_BACK))
				go = false;

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
				inputManager.HandleGamepadEvent(incomingEvent);
				break;

			case SDL_KEYDOWN:
			case SDL_KEYUP:
				inputManager.HandleKeyboardEvent(incomingEvent);
				break;

			case SDL_QUIT:
				go = false;
				break;
			}
		}


		//while(true)
		//{
		int menuChoice = -1;
		system("cls");
		switch(state)
		{
		case MENU:
			menuChoice = menu->Update();
			if (menuChoice == 0)
				state = INGAME;
			else if (menuChoice ==1 )
				state = CREDITS;
			else if (menuChoice == 2)
				go = false;

			SDL_SetRenderDrawColor( renderer, 0x0, 0x0, 0x0, 0xFF );
			SDL_RenderClear(renderer);
			background->Draw(0, 0, winWidth, winHeight, *renderer);
			menu->Draw(renderer);
			SDL_RenderPresent(renderer);
			break;
				
			case INGAME:
				//---what now?!
				UpdatePlaying(*renderer);
				break;
			
			case CREDITS:
				//---What do we want to do?
				PlayCredits(*renderer);
		

		}
	

		//store current frames time as last time
		lastTime = currentTime;
	}

	delete menu;
	delete background;

	// If we get outside the main game loop, it means our user has requested we exit
	SDL_DestroyWindow( window );
	SDL_Quit();

	return 0;
}


void UpdatePlaying(SDL_Renderer &renderer) {
	cout << "PLAYING!!!!" << endl;
	SDL_SetRenderDrawColor( &renderer, 0x0, 0x0, 0x0, 0xFF );
	SDL_RenderClear(&renderer);
	SDL_RenderPresent(&renderer);
	cin.get();
}

void PlayCredits(SDL_Renderer &renderer)
{
	cout << "Credits!!!!!" << endl;
	SDL_SetRenderDrawColor( &renderer, 0x0, 0x0, 0x0, 0xFF );
	SDL_RenderClear(&renderer);
	SDL_RenderPresent(&renderer);
	cin.get();
}

