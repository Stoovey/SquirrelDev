#include"gameObject.h"	

gameObject::gameObject(){

}

gameObject::~gameObject(){

}

void gameObject::draw(SDL_Surface* screen){
	SDL_BlitSurface(displaySprite->getImage(), &displaySprite->getOffset(), screen, &pos);

}

void gameObject::setDisplaySprite(sprite* spr){
	displaySprite = spr;
}

void gameObject::update(SDL_Surface* screen){
	displaySprite->annimate(true);
}

void gameObject::setActive(bool ta){
	active = ta;
}
void gameObject::setAlive(bool ta){
	alive = ta;
}

bool gameObject::getActive(){
	return active;
}
bool gameObject::getAlive(){
	return alive;
}

void gameObject::setState(int ts){
	state = ts;
}
int gameObject::getState(){
	return state;
}