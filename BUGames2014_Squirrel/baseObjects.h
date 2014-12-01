#ifndef BASEOBJECTS_H
#define BASEOBJECTS_H

#include <SDL.h>

/*--------------------------------------
	class baseObjects
		contains position information for
		objects
--------------------------------------*/

class baseObjects{
protected:
	SDL_Rect	pos;
public:
	void setX(int x);
	void setY(int y);
	void setW(int w);
	void setH(int h);

	int getX();
	int getY();
	int getW();
	int getH();

	SDL_Rect getPos();
};

#endif