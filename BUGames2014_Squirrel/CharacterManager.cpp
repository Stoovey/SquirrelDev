#include "CharacterManager.h"

CharacterManager::CharacterManager(SDL_Renderer* render, InputManager* input) {
	this->input = input;
	
	players.push_back(new TestCharacter("Assets/character_sprite.png", *render, input));
	players.push_back(new TestCharacter("Assets/character_sprite2.png", *render, input));
	players.push_back(new TestCharacter("Assets/character_sprite4.png", *render, input));
	players.push_back(new TestCharacter("Assets/character_sprite5.png", *render, input));

	for (int i = 0; i < 4; i++) {
		scoreUI.push_back(new Sprite("Assets/UI/press_start.png", render));
	}


	/*-----------------------------------
	Setting up Vector of numbers
	----------------------------------*/
	for (int i = 0; i < 11; i++) {
		if(i == 0){ 
		numbersUI.push_back(new Sprite("Assets/UI/score0.png", render));
		}
		if(i == 1){ 
		numbersUI.push_back(new Sprite("Assets/UI/score1.png", render));
		}
		if(i == 2){ 
		numbersUI.push_back(new Sprite("Assets/UI/score2.png", render));
		}
		if(i == 3){ 
		numbersUI.push_back(new Sprite("Assets/UI/score3.png", render));
		}
		if(i == 4){ 
		numbersUI.push_back(new Sprite("Assets/UI/score4.png", render));
		}
		if(i == 5){ 
		numbersUI.push_back(new Sprite("Assets/UI/score5.png", render));
		}
		if(i == 6){ 
		numbersUI.push_back(new Sprite("Assets/UI/score6.png", render));
		}
		if(i == 7){ 
		numbersUI.push_back(new Sprite("Assets/UI/score7.png", render));
		}
		if(i == 8){ 
		numbersUI.push_back(new Sprite("Assets/UI/score8.png", render));
		}
		if(i == 9){ 
		numbersUI.push_back(new Sprite("Assets/UI/score9.png", render));
		}
		if(i >= 10){
		numbersUI.push_back(new Sprite("Assets/win.jpeg", render));
		}
	}
}

CharacterManager::~CharacterManager() {
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++)
		delete (*iter);

}

void CharacterManager::AddPlayer(int padID) {
	//make sure pad id is not in use already
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++) {
		if ((*iter)->GetPadID() == padID)
			return;
	}

	//activate the new player
	for (iter = players.begin(); iter != players.end(); iter++) {
		if (!(*iter)->GetIsActive()) {
			(*iter)->Activate(padID);
			break;
		}
	}
}

void CharacterManager::RemovePlayer(int padID) {
	
}

void CharacterManager::Update(unsigned int deltaTime) {
	//respawn any player who have gone offscreen
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++) {
		if ((*iter)->GetIsActive() && (*iter)->GetState() == PlayerState::Dead)
			(*iter)->RespawnPlayer();
	}
	
	for (iter = players.begin(); iter != players.end(); iter++) {
		if ((*iter)->GetIsActive())
			(*iter)->Update(deltaTime);
	}
}
	
void CharacterManager::Draw(SDL_Renderer* render) {
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++) {
		if ((*iter)->GetIsActive())
			(*iter)->Draw(*render);
	}
	
	location = 0;
	for (int i = 0; i < 4; i++) {

		if (players.at(i)->GetIsActive())
		{
			//players.at(i)->GetScore();
			scoreUI.at(i) = numbersUI.at(players.at(i)->GetScore());
			scoreUI.at(i)->Draw((location + (375*i)), 0, 130, 100, *render);
		} 
		else //if player not being used
		{
			scoreUI.at(i)->Draw((location + (300*i)), 0, 240, 45, *render);//draw a "press start"
				
		}
	}
}