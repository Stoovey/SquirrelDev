#include "ItemBase.h"

ItemBase::ItemBase(LevelManager* theLevel, CharacterManager* playerManager, InputManager* input) {
	this->theLevel = theLevel;
	this->playerManager = playerManager;
	this->input = input;

	collision = new CollisionHelper();
}

ItemBase::~ItemBase() {
	delete collision;
}

