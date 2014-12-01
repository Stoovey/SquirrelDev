#include "ActionState.h"

ActionState::ActionState(GamestateManager* stateManager, SDL_Renderer* renderer, InputManager* input, int startingPadId, int winWidth, int winHeight) {
	this->stateManager = stateManager;
	this->input = input;
	this->renderer = renderer;
	this->winHeight = winHeight;
	this->winWidth = winWidth;

	characterManager = new CharacterManager(renderer, input);
	characterManager->AddPlayer(startingPadId);

	theLevel = new level();
	collision = new Collision();
	theLevel->init(renderer);

	itemManager = new ItemManager(theLevel, characterManager, renderer, input);
	itemManager->SpawnAcorn();

	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Background_scaled.png", renderer), .01f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Clouds_scaled.png", renderer), .03f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Foliage_scaled.png", renderer), 0.f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Middleground_scaled.png", renderer), 0.f, winWidth, winHeight));
	backgrounds.push_back(new TiledScrollingBkg(new Sprite("Assets/Foreground_scaled.png", renderer), 0.f, winWidth, winHeight));
}

ActionState::~ActionState() {
	delete testCharacter;
	delete theLevel;
	delete collision;
	delete characterManager;
	delete itemManager;

	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		delete (*iter);
}

void ActionState::Update(unsigned int deltaTime) {

	//character stuff
	characterManager->Update(deltaTime);
	DoCollisions();

	//item handling
	itemManager->Update(deltaTime);

	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Update(deltaTime);

	//check for people pressing start, add the to the game if possible
	int startPadIndex = input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_START);
	if (startPadIndex != -1) {
		characterManager->AddPlayer(startPadIndex);
	}

	CheckHasAnyoneWon();

	if(input->WasKeyPressed(SDLK_ESCAPE) || input->WasPadButtonPressedByAnyPad(SDL_CONTROLLER_BUTTON_BACK) != -1)
	{
		//stateManager->RemoveAllStates();
		stateManager->AddState(new PausedState(stateManager, renderer, input, winWidth, winHeight));
	}
}

void ActionState::CheckHasAnyoneWon() {
	for (int i = 0; i < characterManager->GetPlayers().size(); i++) {
		if (characterManager->GetPlayers().at(i)->GetScore() >= 10) {
			stateManager->RemoveAllStates();
			stateManager->AddState(new WinState(characterManager,stateManager, renderer, input, winWidth, winHeight));
		}
	}
}

void ActionState::DoCollisions() {

	DoPlayerAttacks();

	std::vector<CharacterBase*>::iterator iter;
	for (iter = characterManager->GetPlayers().begin(); iter != characterManager->GetPlayers().end(); iter++) {
		
		if (!(*iter)->GetIsActive()) continue;

		//if falling collision tests
		if ((*iter)->GetState() == PlayerState::Falling) {
			for (int i = 0; i < theLevel->GetPlatformBlocks()->size(); i++) {
				if (collision->boxCollision(
					(*iter)->getX(),
					(*iter)->getY(), 
					(*iter)->getW(), 
					(*iter)->getH(),
					theLevel->GetPlatformBlocks()->at(i)->getX(), 
					theLevel->GetPlatformBlocks()->at(i)->getY(), 
					theLevel->GetPlatformBlocks()->at(i)->getW(), 
					theLevel->GetPlatformBlocks()->at(i)->getH())) {

						if((*iter)->getY()+(*iter)->getH() <= theLevel->GetPlatformBlocks()->at(i)->getY()+10)
							(*iter)->SetState(PlayerState::Normal);
				}
			}
		//if normal collision tests
		} else if ((*iter)->GetState() == PlayerState::Normal) {

			bool noHit = true;

			for (int i = 0; i < theLevel->GetPlatformBlocks()->size(); i++) {
				if (collision->boxCollision(
					(*iter)->getX(),
					(*iter)->getY(), 
					(*iter)->getW(), 
					(*iter)->getH(),
					theLevel->GetPlatformBlocks()->at(i)->getX(), 
					theLevel->GetPlatformBlocks()->at(i)->getY(), 
					theLevel->GetPlatformBlocks()->at(i)->getW(), 
					theLevel->GetPlatformBlocks()->at(i)->getH())) {

						noHit = false;
						break;
				}
			}
			if (noHit)
				(*iter)->SetState(PlayerState::Falling);
		}
	}
}

void ActionState::Draw(SDL_Renderer* renderer) {
	
	std::vector<TiledScrollingBkg*>::iterator iter;
	for (iter = backgrounds.begin(); iter != backgrounds.end(); iter++)
		(*iter)->Draw(renderer);

	theLevel->drawLevel(renderer);
	itemManager->Draw(renderer);
	characterManager->Draw(renderer);
}

void ActionState::DoPlayerAttacks() {
	std::vector<CharacterBase*>& players = characterManager->GetPlayers();

	for (int i = 0; i < players.size(); i++) {
		if (!players.at(i)->GetIsActive()) continue;

		//if player i has pressed B (attack)
		if (input->WasPadButtonPressed(players.at(i)->GetPadID(), SDL_CONTROLLER_BUTTON_B)) {
			
			//iterate over the other player, check for collisions
			for (int j = 0; j < players.size(); j++) {
				//don't check against self
				if (j == i) continue;
				if (!players.at(j)->GetIsActive()) continue;

				if (collision->boxCollision(
					players.at(i)->getX(),
					players.at(i)->getY(),
					players.at(i)->getW(),
					players.at(i)->getH(),
					players.at(j)->getX(),
					players.at(j)->getY(),
					players.at(j)->getW(),
					players.at(j)->getH())) {
				
						//player on player collision, with attacking
						//std::cout << "Player on player attack" << std::endl;
						if (itemManager->GetAcornItem()) {
							if (itemManager->GetAcornItem()->GetPlayerHoldingThis() == players.at(j)) {
								itemManager->GetAcornItem()->ThrowFromPlayer();
							}
						}
	
				}
			}
		}
	}
}
