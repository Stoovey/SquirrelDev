#ifndef level_h
#define level_h

#include "Services.h"
#include "Sprite.h"
#include "Vector2D.h"
#include <SDL.h>
#include <vector>
#include <time.h>

class LevelManager : public ServiceBase {

public:
	//ctor / dtor
	LevelManager(Services* services);
	~LevelManager();

	void drawLevel(SDL_Renderer* render);

	std::vector<Sprite*>* GetPlatformBlocks();
	Vector2D* GetAGoalLocation();

protected:	

	Sprite* grass;

private:

	std::vector<Sprite*>* platformBlocks;
	std::vector<Vector2D*>* goalLocations;

	void PopulateBlocksVector(SDL_Renderer* render);
};
#endif