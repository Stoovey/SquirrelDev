/*----------------------------
Collision.H
by: Alexander Jones
----------------------------*/
#ifndef Collision_h
#define Collision_h

#include "Services.h"

class CollisionHelper : public ServiceBase {
	private:

	protected:
		
		int x1, y1,  w1,  h1, x2, y2, w2, h2;
	public:
		CollisionHelper();
		~CollisionHelper();
		bool boxCollision(int x1, int y1,int w1, int h1,int x2,int  y2,int w2,int h2);
		bool circleCollision(int Cx1, int Cy1,int Cw1, int Ch1,int Cx2,int  Cy2,int Cw2,int Ch2);
};

#endif