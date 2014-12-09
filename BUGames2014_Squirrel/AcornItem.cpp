#include "AcornItem.h"

AcornItem::AcornItem(level* theLevel, CharacterManager* playerManager, SDL_Renderer* renderer, InputManager* input) : ItemBase(theLevel, playerManager, input) {
	acornSprite = new Sprite("Assets/Items/Acorn.png", 0, 0, 64, 64, *renderer);
	
	vel.Y = .25f;
	vel.X = 0.f;

	playerHoldingThis = NULL;
	lastPlayerHoldingThis = NULL;

	hasFiniteLifespan = false;

	samePlayerHoldingTimerReset = 250;
	samePlayerHoldingTimer = samePlayerHoldingTimerReset;

	cannotBeHeldTimerReset = 250;
	cannotBeHeldTimer = cannotBeHeldTimerReset;

}

void AcornItem::Update(unsigned int deltaTime) {

	CheckInBounds();

	switch (itemState) {
	case ItemState::Standard:
		UpdateNormal(deltaTime);
		break;
	case ItemState::Fall:
		UpdateFalling(deltaTime);
		break;
	case ItemState::Collected:
		UpdateCollected(deltaTime);
		break;
	case ItemState::Thrown:
		UpdateThrown(deltaTime);
		break;
	}
}

void AcornItem::UpdateNormal(unsigned int deltaTime) {

	playerHoldingThis = CheckCollisionPlayer();
	if (playerHoldingThis)
		itemState = ItemState::Collected;

	if (!CheckCollideScenery())
		itemState = ItemState::Fall;
}

void AcornItem::UpdateFalling(unsigned int deltaTime) {

	pos.X += vel.X * deltaTime;
	pos.Y += vel.Y * deltaTime;

	CharacterBase* playerCheck = CheckCollisionPlayer();
	if (playerCheck) {
		lastPlayerHoldingThis = playerHoldingThis;
		playerHoldingThis = playerCheck;
		itemState = ItemState::Collected;
	}

	if (CheckCollideScenery())
		itemState = ItemState::Standard;
}

void AcornItem::UpdateCollected(unsigned int deltaTime) {
	if (!playerHoldingThis || playerHoldingThis->GetState() == PlayerState::Dead) {
		itemState = ItemState::Fall;
		return;
	}
	
	Vector2D toPlayer = Vector2D(playerHoldingThis->getPos().x - pos.X, playerHoldingThis->getPos().y - pos.Y);
	if (toPlayer.Length() > playerHoldingThis->getW() / 4.f) {
		pos.X += (toPlayer.X / 60.f) * deltaTime;
		pos.Y += (toPlayer.Y / 60.f) * deltaTime;
	}

	bool shortThrow = abs(input->GetPadAxisValue(playerHoldingThis->GetPadID(), SDL_CONTROLLER_AXIS_RIGHTX)) < 0.2f &&
		abs(input->GetPadAxisValue(playerHoldingThis->GetPadID(), SDL_CONTROLLER_AXIS_RIGHTY)) < 0.2f;

	if (abs(input->GetPadAxisValue(playerHoldingThis->GetPadID(), SDL_CONTROLLER_AXIS_LEFTX)) > 0.2f)
		lastMovedLeft = input->GetPadAxisValue(playerHoldingThis->GetPadID(), SDL_CONTROLLER_AXIS_LEFTX) < 0;

	if (input->GetPadAxisValue(playerHoldingThis->GetPadID(), SDL_CONTROLLER_AXIS_TRIGGERRIGHT) > 0.5f) {
		vel.X = input->GetPadAxisValue(playerHoldingThis->GetPadID(), SDL_CONTROLLER_AXIS_RIGHTX);
		vel.Y = input->GetPadAxisValue(playerHoldingThis->GetPadID(), SDL_CONTROLLER_AXIS_RIGHTY);

		if (shortThrow) {
			vel.X = 0.35f;
			if (lastMovedLeft)
				vel.X *= -1;
		}

		if (shortThrow) {
			if (vel.Y > 0) 
				vel.Y = 0.35f;
			else
				vel.Y = -0.35f;
		}

		vel.X *= 1.5f;
		vel.Y *= 1.f;
		throwVelY = abs(vel.Y);

		samePlayerHoldingTimer = samePlayerHoldingTimerReset;
		itemState = ItemState::Thrown;
	}
}

void AcornItem::UpdateThrown(unsigned int deltaTime) {
	
	//no point doing anything if and SDL 'tick' has not occured
	if (deltaTime == 0) return;
	
	pos.X += vel.X * deltaTime;
	pos.Y += vel.Y * deltaTime;

	if (samePlayerHoldingTimer > 0)
		samePlayerHoldingTimer -= deltaTime;

	if (cannotBeHeldTimer > 0)
		cannotBeHeldTimer -= deltaTime;

	Sprite* scenery = CheckCollideScenery(); 
	if (scenery) {
		if (pos.Y < scenery->getY() - (acornSprite->GetHeight() * 0.95f)) {
			itemState = ItemState::Standard;
		}
	}

	vel.Y += .0025f * deltaTime;
	if (vel.Y > 0 && vel.Y < throwVelY / 2)
		vel.Y = throwVelY / 2;

	CharacterBase* playerCheck = CheckCollisionPlayer();
	if (cannotBeHeldTimer < 0 && playerCheck && (playerCheck != playerHoldingThis || samePlayerHoldingTimer <= 0)) {
		lastPlayerHoldingThis = playerHoldingThis;
		playerHoldingThis = playerCheck;
		itemState = ItemState::Collected;
	}
}

void AcornItem::Draw(SDL_Renderer* renderer) {
	acornSprite->Draw((int)pos.X, (int)pos.Y, acornSprite->getW(), acornSprite->getH(), *renderer);
}

void AcornItem::Spawn(int x, int y) {
	pos.X = (float)x;
	pos.Y = (float)y;
	playerHoldingThis = NULL;
	itemState = ItemState::Standard;
}

void AcornItem::Destroy() {

}

void AcornItem::CheckInBounds() {
	if (pos.X < -acornSprite->GetWidth() || pos.X > 1280 || pos.Y > 700)
		itemState = ItemState::Die;
}

bool AcornItem::DoGoalCheck(std::vector<ItemBase*>& goalItems) {
	for (unsigned int i = 0; i < goalItems.size(); i++) {
		if (collision->boxCollision(
			(int)pos.X,
			(int)pos.Y, 
			acornSprite->GetWidth(), 
			acornSprite->GetHeight(),
			(int)goalItems.at(i)->GetPos().X, 
			(int)goalItems.at(i)->GetPos().Y, 
			goalItems.at(i)->GetWidth(), 
			goalItems.at(i)->GetHeight())) {

			CharacterBase* scoringPlayer = NULL;

			if (playerHoldingThis != NULL) 
				scoringPlayer = playerHoldingThis;
			else if (lastPlayerHoldingThis != NULL)
				scoringPlayer = lastPlayerHoldingThis;

			if (scoringPlayer) {
				scoringPlayer->AdjustScore(1);
				itemState = ItemState::Die;
				return true;
			}
			return false;
		}
	}
	return false;
}

Sprite* AcornItem::CheckCollideScenery() {

	for (unsigned int i = 0; i < theLevel->GetPlatformBlocks()->size(); i++) {
		if (collision->boxCollision(
			(int)pos.X,
			(int)pos.Y, 
			acornSprite->GetWidth(), 
			acornSprite->GetHeight(),
			(int)theLevel->GetPlatformBlocks()->at(i)->getX(), 
			(int)theLevel->GetPlatformBlocks()->at(i)->getY(), 
			theLevel->GetPlatformBlocks()->at(i)->getW(), 
			theLevel->GetPlatformBlocks()->at(i)->getH())) {

				return theLevel->GetPlatformBlocks()->at(i);
		}
	}

	return NULL;
}

CharacterBase* AcornItem::CheckCollisionPlayer() {
	
	for (unsigned int i = 0; i < playerManager->GetPlayers().size(); i++) {
		if (collision->boxCollision(
			(int)pos.X, (int)pos.Y, acornSprite->GetWidth(), acornSprite->GetHeight(),
			(int)playerManager->GetPlayers().at(i)->getX(),
			(int)playerManager->GetPlayers().at(i)->getY(),
			playerManager->GetPlayers().at(i)->getW(),
			playerManager->GetPlayers().at(i)->getH())) {

				return playerManager->GetPlayers().at(i);		
		}
	}

	return NULL;
}

int AcornItem::GetWidth() {
	return acornSprite->GetWidth();
}
	
int AcornItem::GetHeight() {
	return acornSprite->GetHeight();
}

void AcornItem::ThrowFromPlayer() {
	float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	y = 1;
	x -= 0.5f;
	
	if (x < 0) 
		x -= 0.5f;
	else
		x += 0.5f;

	vel.Y = -y;
	vel.X = x;

	cannotBeHeldTimer = cannotBeHeldTimerReset;
	itemState = ItemState::Thrown;
}