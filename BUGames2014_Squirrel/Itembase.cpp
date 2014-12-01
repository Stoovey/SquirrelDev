#include "ItemBase.h"

ItemBase::ItemBase(level* theLevel, CharacterManager* playerManager, InputManager* input) {
	this->theLevel = theLevel;
	this->playerManager = playerManager;
	this->input = input;

	collision = new Collision();
}

ItemBase::~ItemBase() {
	delete collision;
}

