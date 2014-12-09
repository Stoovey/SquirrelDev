#include"baseObjects.h"	
/*--------------------------------------
		baseObjects setters
--------------------------------------*/
	void baseObjects::setX(float x){
		pos.x = (int)x;
	}
	void baseObjects::setY(float y){
		pos.y = (int)y;
	}
	void baseObjects::setW(int w){
		pos.w = w;
	}
	void baseObjects::setH(int h){
		pos.h = h;
	}


/*--------------------------------------
		baseObjects getters
--------------------------------------*/
	float baseObjects::getX(){
		return (float)pos.x;
	}
	float baseObjects::getY(){
		return (float)pos.y;
	}
	int baseObjects::getW(){
		return pos.w;
	}
	int baseObjects::getH(){
		return pos.h;
	}
	SDL_Rect baseObjects::getPos(){
		return pos;
	}