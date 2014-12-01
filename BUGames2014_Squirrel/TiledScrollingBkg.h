#pragma once

#include "Sprite.h"
#include <iostream>

class TiledScrollingBkg {

public:
	//constructor / destructor
	TiledScrollingBkg(Sprite* image, float speed, int screenWidth, int screenHeight);
	~TiledScrollingBkg();

	//update (move) and draw the background
	void Update(unsigned int deltaTime);
	void Draw(SDL_Renderer* renderer);

private:
	//the sprite being used as abkg, and how fast to scroll
	Sprite* image;
	float speed;

	//height of screen, need this to know when a tile has scrolled off the bottom
	int screenHeight;
	int screenWidth;

	//number of tiles in X/Y, calculated automatically in the constructor
	int numImagesX;
	int numImagesY;

	//where to start the first tile in Y, updated in Update()
	float imageXOffset;
};