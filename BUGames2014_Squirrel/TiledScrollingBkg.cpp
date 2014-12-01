#include "TiledScrollingBkg.h"

//constructor
TiledScrollingBkg::TiledScrollingBkg(Sprite* image, float speed, int screenWidth, int screenHeight) {
	/* store values passed to constructor in member variables
	 * except screenWidth which we will never need after this */
	this->image = image;
	this->speed = speed;
	this->screenHeight = screenHeight;
	this->screenWidth = screenWidth;

	/* this will be the first tiles Y position, it will start
	 * at minus "image height", meaning the first tile will begin
	 * just out of view and scroll down onto the screen */
	this->imageXOffset = (float)-image->GetWidth();

	/** Number of tiles we need in X/Y to fill the screen (or window)
	  * the '+1' and '+2' are needed to get the images to fill the
	  * space up (comment them out and run it to see what I mean) */
	this->numImagesX =  (screenWidth / image->GetWidth()) + 2; 
	this->numImagesY =  (screenHeight / image->GetHeight()) + 1; 
}

//destructor
TiledScrollingBkg::~TiledScrollingBkg() {
	delete this->image;
}

void TiledScrollingBkg::Update(unsigned int deltaTime) {

	imageXOffset += speed * deltaTime;

	//make sure image covers left of screen
	if (imageXOffset >= 0)
		imageXOffset -= image->GetWidth(); 
}

void TiledScrollingBkg::Draw(SDL_Renderer* renderer) {
	int x = (int)imageXOffset;
	int y = 0;

	//for every row of tiles...
	for (int i = 0; i < numImagesY; i++) {
		x = imageXOffset;
		//for every tile in the row...
		for (int j = 0; j < numImagesX; j++) {
			
			//draw the tile
			image->Draw(x, y, *renderer);
			
			/* comment out the above line and use the below one
			 * if your Sprite class does not have the 
			 * Draw(int, int, renderer&) function */
			
			//image->Draw(x, y, image->GetWidth(), image->GetHeight(), renderer);

			//work out the next tiles X position
			x += image->GetWidth();
		}
		//work out the next row of tiles Y position
		y += image->GetHeight();
	}
}