
#ifndef __SPRITE_H__
#define __SPRITE_H__

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include "baseObjects.h"

/// This class stores a texture image which you can draw where you want!
class Sprite : public baseObjects
{
public:

	Sprite();
	~Sprite();

	Sprite(std::string filename, SDL_Renderer *renderer);
	Sprite(std::string filename, int positionX, int positionY, int width, int height, SDL_Renderer& renderer);
	/// Loads a .bmp file, returns true on success or false on failure
	bool LoadFromIMG( std::string filename, SDL_Renderer *renderer );

	/// Specify the position of the top-left corner of the sprite
	/// Width and height are the image's original
	virtual void Draw( int positionX, int positionY, SDL_Renderer& renderer );
	virtual void Draw(SDL_Renderer& renderer);
	virtual void Draw( int positionX, int positionY, int width, int height, SDL_Renderer& renderer );

	int GetWidth() { return width; }
	int GetHeight() { return height; }
	float GetAspectRatio() { return (float)width / (float)height; }

protected:

	/// This variable will be our handle for the texture
	SDL_Texture *_texture;

	//texture file width and height
	int width;
	int height;

};





#endif
