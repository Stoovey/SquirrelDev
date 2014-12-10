#include "MenuState.h"
#include <iostream>

//constructor
MenuState::MenuState(Services* services) : GameState(services) {
	
	//get services for this state
	this->config       = (Config*)services->GetService(Service::Config);
	this->stateManager = (GamestateManager*)services->GetService(Service::GameStateManager);
	this->input        = (InputManager*)services->GetService(Service::InputManager);
	this->renderer     = services->GetSDL_Renderer();

	int winWidth  = config->GetWinWidth();
	int winHeight = config->GetWinHeight();

	//add some scrolling background images
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Content/Levels/Background_scaled.png", renderer), .01f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Content/Levels/Clouds_scaled.png", renderer), .03f, winWidth, winHeight));
	
	/* create the sprite which is the main background image, the reason this
	 * is its own sprite is that the Sprite class provides an easy way of 
	 * getting an image to fill the screen, whereas the TiledScrollingBkg
	 * class assumes this is never necessary */
	background = new Sprite("Content/Levels/mainmenu_transparent.png", renderer);
	
	//create the main menu itself
	menu = new Menu(renderer, input);
}

//destructor
MenuState::~MenuState() {
	//delete everything we have 'new-ed' and stored in here
	delete background;
	delete menu;
	
	//get an iterator 'iter' to visit every background in the backgrounds vector
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++) {
		//delete whichever background 'iter' is now at
		delete (*iter);
	}

	//clear the backgrounds vector
	backgrounds.clear();

	std::cout << "MenuState dtor called" << std::endl;
}

//update the menu state
bool MenuState::Update(unsigned int deltaTime) {
	
	//see what menu item was selected, if any
	int menuChoice = menu->Update();

	//menuChoice being 0 means "New Game" was selected
	if (menuChoice == 0) {
		
		/* see if we can get the padID of the "starting" pad, and pass it to ActionStates constructor
		 * if we can't get the starting padID (say the keyboard was used to start the game) then 
		 * just pass 0 for the padID, which is the first player pad */
		int startingPadId = menu->GetSelectingpadId();
		if (startingPadId == -1)
			stateManager->ChangeState(new ActionState(services, 0));
		else
			stateManager->ChangeState(new ActionState(services, startingPadId));

		//this state is now gone, so all we can do is return
		return true;
	}
	//menucChoice of 1 means "Credits" was selected
	else if (menuChoice == 1) {
		//get stateManager to add credits state onto the list
		stateManager->AddState(new CreditsState(services));
	}
	//menuState of 2 means quit was pressed
	else if (menuChoice == 2)
	{
		//quit
		return false;
	}

	//iterate over the backgrounds vector, update each one (allow it to scroll)
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Update(deltaTime);

	return true;
}

//draw menu state
void MenuState::Draw(SDL_Renderer* renderer) {
	//iterate over the backgrounds vector, draw each one
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Draw(renderer);

	//draw the 'static' background and the menu
	background->Draw(0, 0, config->GetWinWidth(), config->GetWinHeight(), *renderer);
	menu->Draw(renderer);
}

