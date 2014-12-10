#include "ActionState.h"

//constructor
ActionState::ActionState(Services* services, int startingPadId) : GameState(services) {

	//grab hold of the services we need for this state
	this->config           = (Config*)services->GetService(Service::Config);
	this->characterManager = (CharacterManager*)services->GetService(Service::CharacterManager);
	this->stateManager     = (GamestateManager*)services->GetService(Service::GameStateManager);
	this->input            = (InputManager*)services->GetService(Service::InputManager);
	this->collision	       = (CollisionHelper*)services->GetService(Service::CollisionHelper);
	this->theLevel         = (LevelManager*)services->GetService(Service::LevelManager);
	this->itemManager      = (ItemManager*)services->GetService(Service::ItemManager);
	this->renderer         = services->GetSDL_Renderer();
	
	//create character manager, add a player with whatever padID we were passed
	characterManager->AddPlayer(startingPadId);

	//create ItemManager and spawn the acorn
	itemManager->SpawnAcorn();

	int winWidth = config->GetWinWidth();
	int winHeight = config->GetWinHeight();

	/* add five background images to the 'backgrounds' memeber (which is a std::vector<TiledScrollingBkg*>)
	 * notice how the last 3 have 0.f passed as their scroll speed, meaning they will stay fixed (tree layers) */
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Content/Levels/Background_scaled.png", renderer),  .01f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Content/Levels/Clouds_scaled.png", renderer),      .03f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Content/Levels/Foliage_scaled.png", renderer),      0.f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Content/Levels/Middleground_scaled.png", renderer), 0.f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Content/Levels/Foreground_scaled.png", renderer),   0.f, winWidth, winHeight));
}

//destructor
ActionState::~ActionState() {
	//delete everything we have 'new-ed' and stored in this class

	//for the backgrounds, we iterate over the vector they are in, deleting each as we go
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		delete (*iter);
}

//update this ActionState
bool ActionState::Update(unsigned int deltaTime) {

	//CharacterManager will handle player updates
	characterManager->Update(deltaTime);
	
	//checks for player-platform collisions (also calls DoPlayerAttacks() ) 
	DoCollisions();

	//itemManager will handle item updates
	itemManager->Update(deltaTime);

	//iterate over the backgrounds vector, call update on each background in it
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Update(deltaTime);

	//check for people pressing start, add the to them game if possible
	int startPadIndex = input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_START);
	if (startPadIndex != -1) {
		characterManager->AddPlayer(startPadIndex);
	}

	//if anyone has pressed escape or X360 Back, get StateManager to throw PausedState onto the states list
	if(input->WasKeyPressed(SDLK_ESCAPE) || input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_BACK) != -1)
	{
		stateManager->AddState(new PausedState(services));
	}

	/* we always want to return after using GameStateManager::ChangeState as it
	 * removes THIS state and deletes it. Continuing to run code in here could
	 * cause a crash */
	if (CheckHasAnyoneWon()) {
		stateManager->ChangeState(new WinState(services));
		return true;
	}

	return true;
}

//see if anyone has met the victory conditions
bool ActionState::CheckHasAnyoneWon() {

	//go over each player in the player list
	for (unsigned int i = 0; i < characterManager->GetPlayers().size(); i++) {
		//if a player has a score of 10, return true
		if (characterManager->GetPlayers().at(i)->GetScore() >= 10) {
			return true;
		}
	}

	//if we get here then no player has won
	return false;
}

//check collisions between things - NEEDS TIDYING / REFACTORING
void ActionState::DoCollisions() {

	//check for player on player attacks
	DoPlayerAttacks();

	//iterate over the player list in characterManager
	std::vector<CharacterBase*>::iterator iter;
	for (iter = characterManager->GetPlayers().begin(); iter != characterManager->GetPlayers().end(); iter++) {
		
		//if the player 'iter' is now at is inactive, continue on to the next
		if (!(*iter)->GetIsActive()) continue;

		//if 'iter' points to a player that is falling...
		if ((*iter)->GetState() == PlayerState::Falling) {

			//...check to see if they touch ANY platform block in the level...
			for (unsigned int i = 0; i < theLevel->GetPlatformBlocks()->size(); i++) {
				if (collision->boxCollision(
					(int)(*iter)->getX(),
					(int)(*iter)->getY(), 
					(*iter)->getW(), 
					(*iter)->getH(),
					(int)theLevel->GetPlatformBlocks()->at(i)->getX(), 
					(int)theLevel->GetPlatformBlocks()->at(i)->getY(), 
					theLevel->GetPlatformBlocks()->at(i)->getW(), 
					theLevel->GetPlatformBlocks()->at(i)->getH())) {

						//...and set their state to 'Normal' (i.e not falling) if they do
						if((*iter)->getY()+(*iter)->getH() <= theLevel->GetPlatformBlocks()->at(i)->getY()+10)
							(*iter)->SetState(PlayerState::Normal);
				}
			}

		//if 'iter' points to a player that is in 'Normal' state (walking about on platforms)
		} else if ((*iter)->GetState() == PlayerState::Normal) {

			//...start by assuming they are not touching a platform now...
			bool noHit = true;

			//...but check them against every platform...
			for (unsigned int i = 0; i < theLevel->GetPlatformBlocks()->size(); i++) {
				if (collision->boxCollision(
					(int)(*iter)->getX(),
					(int)(*iter)->getY(), 
					(*iter)->getW(), 
					(*iter)->getH(),
					(int)theLevel->GetPlatformBlocks()->at(i)->getX(), 
					(int)theLevel->GetPlatformBlocks()->at(i)->getY(), 
					theLevel->GetPlatformBlocks()->at(i)->getW(), 
					theLevel->GetPlatformBlocks()->at(i)->getH())) {

						//...and set our noHit flag to false if we find they do touch a platform
						noHit = false;

						//...then stop checking (if they touch even one platform, thats enough to stop them falling)
						break;
				}
			}

			/* if after all the checks, a 'Normal' player is not touching
			 * a platform then set them to their 'falling' state */
			if (noHit)
				(*iter)->SetState(PlayerState::Falling);
		}
	}
}

//draw the action state
void ActionState::Draw(SDL_Renderer* renderer) {
	
	/* iterate over the backgrounds vector
	 * call Draw on each one */
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Draw(renderer);

	//tell the level, itemManager and characterManager to Draw
	theLevel->drawLevel(renderer);
	itemManager->Draw(renderer);
	characterManager->Draw(renderer);
}

//check for player on player attacks - NEEDS TIDYING UP
void ActionState::DoPlayerAttacks() {

	//obtain a reference to the player list (makes the following code easier)
	std::vector<CharacterBase*>& players = characterManager->GetPlayers();

	//for every player in the players list...
	for (unsigned int i = 0; i < players.size(); i++) {

		//...if they are inactive, continue on to the next
		if (!players.at(i)->GetIsActive()) continue;

		//if player 'i' has pressed B (attack)...
		if (input->WasPadButtonPressed(players.at(i)->GetPadID(), SDL_CONTROLLER_BUTTON_B)) {
			
			//...iterate over the other players, check for collisions between them
			for (unsigned int j = 0; j < players.size(); j++) {
				
				//don't check against self
				if (j == i) continue;
				if (!players.at(j)->GetIsActive()) continue;

				if (collision->boxCollision(
					(int)players.at(i)->getX(),
					(int)players.at(i)->getY(),
					players.at(i)->getW(),
					players.at(i)->getH(),
					(int)players.at(j)->getX(),
					(int)players.at(j)->getY(),
					players.at(j)->getW(),
					players.at(j)->getH())) {
				
						//player on player collision, with one pressing attack

						//if the acorn exists in the itemManager
						if (itemManager->GetAcornItem()) {
							//and the 'other' player is holding it (not the attacker)
							if (itemManager->GetAcornItem()->GetPlayerHoldingThis() == players.at(j)) {
								//tell the acorn to get thrown
								itemManager->GetAcornItem()->ThrowFromPlayer();
							}
						}
	
				}
			}
		}
	}
}
