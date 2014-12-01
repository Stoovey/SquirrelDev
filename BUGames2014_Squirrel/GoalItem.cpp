#include "GoalItem.h"

GoalItem::GoalItem(level* theLevel, CharacterManager* playerManager, SDL_Renderer* renderer, InputManager* input)  : ItemBase(theLevel, playerManager, input) {
	goalSprite = new Sprite("Assets/Items/Goal.png", 0, 0, 90, 90, *renderer);
	
	hasFiniteLifespan = false;
}

GoalItem::~GoalItem() {

}

void GoalItem::Update(unsigned int deltaTime) {

}

void GoalItem::Draw(SDL_Renderer* renderer) {
	goalSprite->Draw(pos.X, pos.Y, goalSprite->GetWidth(), goalSprite->GetHeight(), *renderer);
}

void GoalItem::Spawn(int x, int y) {
	pos.X = x;
	pos.Y = y;
}

void GoalItem::Destroy() {

}

int GoalItem::GetWidth() {
	return goalSprite->GetWidth();
}
	
int GoalItem::GetHeight() {
	return goalSprite->GetHeight();
}