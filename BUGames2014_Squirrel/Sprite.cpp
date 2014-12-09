
#include <iostream>
#include "Sprite.h"

Sprite::Sprite()
{
	// This is the constructor
	// Don't forget to initialise those member variables!
	_texture = NULL;
}

Sprite::Sprite(std::string filename, int positionX, int positionY, int width, int height, SDL_Renderer& renderer) {
	_texture = NULL;

	this->setW(width);
	this->setH(height);
	this->setX((float)positionX);
	this->setY((float)positionY);
	
	LoadFromIMG(filename, &renderer);
	
	//bit hacky, the LoadFromIMG above overrwrites W/H with the image sizes
	this->width = width;
	this->height = height;
}

Sprite::Sprite(std::string filename, SDL_Renderer *renderer) {
	_texture = NULL;

	LoadFromIMG(filename, renderer);
}

Sprite::~Sprite()
{
	// This is the destructor
	// Use SDL to clean up our texture 
	if( _texture )
	{
		SDL_DestroyTexture( _texture );
	}
}

bool Sprite::LoadFromIMG( std::string filename, SDL_Renderer *renderer )
{
	// Just check we're not being given garbage :P
	if( filename.empty() )
	{
		std::cerr<<"ERROR: Sprite::LoadFromIMG - empty filename given"<<std::endl;
		return false;
	}

	// First we load it to what SDL calls a 'surface'
	// This is just a raw collection of pixels
	SDL_Surface * image = IMG_Load( filename.c_str() );
	if( !image )
	{
		// We'll do a quick check here because it's easy to get filenames or directories wrong
		std::cerr<<"ERROR: Sprite::LoadFromBMP - Oh dear, sorry but I can't find your image file. This brings me great sadness :("<<std::endl;
		return false;
	}

	// Next we convert the SDL_Surface into what it calls a 'texture'
	// This is kinda similar, but because it's bound to a renderer, SDL can make some useful optimisations behind the scenes
	// This will make it draw to the screen faster
	_texture = SDL_CreateTextureFromSurface(renderer, image);

	//query texture for its size and store that away
	SDL_QueryTexture(_texture, NULL, NULL, &width, &height);

	// We've now finished with our raw pixel data, so we can get rid of it
	SDL_FreeSurface(image);

	return true;
}

void Sprite::Draw(SDL_Renderer& renderer) {
	Draw((int)getX(), (int)getY(), this->getW(), this->getH(), renderer);
}

void Sprite::Draw( int positionX, int positionY, SDL_Renderer& renderer ) {
	Draw(positionX, positionY, width, height, renderer);
}

void Sprite::Draw( int positionX, int positionY, int width, int height, SDL_Renderer& renderer ) {
// This will specify where to draw the sprite
	SDL_Rect destRect;
	// SDL has (0,0) at the top left corner - check this by playing about with the numbers!
	destRect.x = positionX;
	destRect.y = positionY;
	destRect.w = width;
	destRect.h = height;

	// Here we are telling the renderer to copy the texture memory to our screen,
	// at the position of the rectangle we specify
	// The parameter that's currently NULL can be used to specify another rectangle that's a sub-region of the whole image
	// This is for doing sprite animation type effects
	SDL_RenderCopy(&renderer, _texture, NULL, &destRect);

}
