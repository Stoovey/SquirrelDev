#include "CharacterManager.h"

//constructor
CharacterManager::CharacterManager(SDL_Renderer* render, InputManager* input) {
	this->input = input;
	
	//add four players to the players list, use a different sprite for each
	players.push_back(new TestCharacter("Assets/character_sprite.png", *render, input));
	players.push_back(new TestCharacter("Assets/character_sprite2.png", *render, input));
	players.push_back(new TestCharacter("Assets/character_sprite4.png", *render, input));
	players.push_back(new TestCharacter("Assets/character_sprite5.png", *render, input));

	//the four player score UI parts, put a "Press Start" in them all to begin with
	for (int i = 0; i < 4; i++) {
		scoreUI.push_back(new Sprite("Assets/UI/press_start.png", render));
	}

	/*-----------------------------------
	Setting up Vector of numbers
	----------------------------------*/
	numbersUI.push_back(new Sprite("Assets/UI/score0.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score1.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score2.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score3.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score4.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score5.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score6.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score7.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score8.png", render));
	numbersUI.push_back(new Sprite("Assets/UI/score9.png", render));
	numbersUI.push_back(new Sprite("Assets/win.jpeg", render));
}

//destructor
CharacterManager::~CharacterManager() {
	//delete all the characters in the std::vector
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++)
		delete (*iter);

}

/* allow a new player to join, gets called when start is pressed
 * padID is the SDL code for whichever pad it is */
void CharacterManager::AddPlayer(int padID) {
	//make sure pad id is not in use already
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++) {
		if ((*iter)->GetPadID() == padID)
			return;
	}

	//activate the new player
	//iterate over the players list...
	for (iter = players.begin(); iter != players.end(); iter++) {
		//if we find an inactive player...
		if (!(*iter)->GetIsActive()) {
			//activate them and pass them the padID
			(*iter)->Activate(padID);
			break;
		}
	}
}

//Remove a player from the game
void CharacterManager::RemovePlayer(int padID) {
	//not implemented yet
}

//update the character manager, this will update all active players
void CharacterManager::Update(unsigned int deltaTime) {
	/* respawn any player who have died */
	//iterate over the player list
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++) {
		//if any player is active and in a dead state then call their respawn function
		if ((*iter)->GetIsActive() && (*iter)->GetState() == PlayerState::Dead)
			(*iter)->RespawnPlayer();
	}
	
	//iterate over the players, if any are active then call their update function
	for (iter = players.begin(); iter != players.end(); iter++) {
		if ((*iter)->GetIsActive())
			(*iter)->Update(deltaTime);
	}
}

//draw all the active players
void CharacterManager::Draw(SDL_Renderer* render) {
	//iterate over the players list
	std::vector<CharacterBase*>::iterator iter;
	for (iter = players.begin(); iter != players.end(); iter++) {
		//if any are active then call their draw function
		if ((*iter)->GetIsActive())
			(*iter)->Draw(*render);
	}
	
	/* UI drawing code */
	location = 0;
	//iterate 'i' from 0-3
	for (int i = 0; i < 4; i++) {
		//if the 'ith' player is active...
		if (players.at(i)->GetIsActive())
		{
			//get their score as a sprite and draw it in the right place.
			scoreUI.at(i) = numbersUI.at(players.at(i)->GetScore());
			scoreUI.at(i)->Draw((location + (375*i)), 0, 130, 100, *render);
		} 
		else //if the 'ith' player is not active...
		{
			//their scoreUI will still have the "Press Start" sprite in it
			scoreUI.at(i)->Draw((location + (300*i)), 0, 240, 45, *render);
		}
	}
}