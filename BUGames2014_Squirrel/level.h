#ifndef level_h
#define level_h

#include "Sprite.h"
#include "Vector2D.h"
#include <SDL.h>
#include <vector>
#include <time.h>

class level{
protected:
	Sprite* grass;
public:
	level();
	~level();
	void init(SDL_Renderer* render);
	void drawLevel(SDL_Renderer* render);

	std::vector<Sprite*>* GetPlatformBlocks();
	Vector2D* GetAGoalLocation();

private:
	std::vector<Sprite*>* platformBlocks;
	std::vector<Vector2D*>* goalLocations;

	void PopulateBlocksVector(SDL_Renderer* render);
};
#endif