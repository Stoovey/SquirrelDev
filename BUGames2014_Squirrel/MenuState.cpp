#include "MenuState.h"
#include <iostream>

//constructor
MenuState::MenuState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int winWidth, int winHeight) {
	
	//store incoming parameters in memeber vars
	this->stateManager = stateManager;
	this->renderer = renderer;
	this->input = input;
	this->winWidth = winWidth;
	this->winHeight = winHeight;

	//add some scrolling background images
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Background_scaled.png", renderer), .01f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Clouds_scaled.png", renderer), .03f, winWidth, winHeight));
	
	/* create the sprite which is the main background image, the reason this
	 * is its own sprite is that the Sprite class provides an easy way of 
	 * getting an image to fill the screen, whereas the TiledScrollingBkg
	 * class assumes this is never necessary */
	background = new Sprite("Assets/mainmenu_transparent.png", renderer);
	
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
void MenuState::Update(unsigned int deltaTime) {
	
	//see what menu item was selected, if any
	int menuChoice = menu->Update();

	//menuChoice being 0 means "New Game" was selected
	if (menuChoice == 0) {
		
		//get state manager to remove all current states
		stateManager->RemoveAllStates();

		/* see if we can get the padID of the "starting" pad, and pass it to ActionStates constructor
		 * if we can't get the starting padID (say the keyboard was used to start the game) then 
		 * just pass 0 for the padID, which is the first player pad */
		int startingPadId = menu->GetSelectingpadId();
		if (startingPadId == -1)
			stateManager->AddState(new ActionState(stateManager, renderer, input, 0, winWidth, winHeight));
		else
			stateManager->AddState(new ActionState(stateManager, renderer, input, startingPadId,  winWidth, winHeight));

		//delete ourselves and return, this needs refactoring
		delete this;
		return;
	}
	//menucChoice of 1 means "Credits" was selected
	else if (menuChoice == 1) {
		//get stateManager to add credits state onto the list
		stateManager->AddState(new CreditsState(stateManager, renderer, input, winWidth, winHeight));
	}
	//menuState of 2 means quit was pressed
	else if (menuChoice == 2)
	{
		//quit
		exit(0); //needs changing
	}

	//iterate over the backgrounds vector, update each one (allow it to scroll)
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Update(deltaTime);

}

//draw menu state
void MenuState::Draw(SDL_Renderer* renderer) {
	//iterate over the backgrounds vector, draw each one
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Draw(renderer);

	//draw the 'static' background and the menu
	background->Draw(0, 0, winWidth, winHeight, *renderer);
	menu->Draw(renderer);
}

