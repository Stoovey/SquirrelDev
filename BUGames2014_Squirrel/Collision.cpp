#include "Collision.h"

Collision::Collision() {

}

Collision::~Collision() {
}

/*----------------------------
Box to Box collision
by: Alexander Jones
----------------------------*/
bool Collision::boxCollision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){ //function call
	if((x1 >= x2 && x1 <= (x2 + w2)) || ((x1 + w1) >= x2 && (x1 + w1) <= (x2 + w2))){ //Check for collision on the left and right side
		if((y1 >= y2 && y1 <= (y2 + h2)) || ((y1 + h1) >= y2 && (y1 + h1) <= (y2 + h2))){ //check for collision on the top and bottom
			return true; //return true for boolion
		}
	}
	return false; //return false for boolion
}

/*----------------------------
Circle to Circle collision
by: Alexander Jones
----------------------------*/
bool Collision::circleCollision(int Cx1, int Cy1,int Cw1, int Ch1,int Cx2,int  Cy2,int Cw2,int Ch2){

	return false;
}