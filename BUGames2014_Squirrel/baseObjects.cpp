#include"baseObjects.h"	
/*--------------------------------------
		baseObjects setters
--------------------------------------*/
	void baseObjects::setX(int x){
		pos.x = x;
	}
	void baseObjects::setY(int y){
		pos.y = y;
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
	int baseObjects::getX(){
		return pos.x;
	}
	int baseObjects::getY(){
		return pos.y;
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