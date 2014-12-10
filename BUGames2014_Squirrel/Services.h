#ifndef _SERVICES_H_
#define _SERVICES_H_

#include <map>
#include <SDL.h>
#include "ServiceBase.h"

/* the names of every class that can be a service.
 * ideally, these should be interfaces (can talk about that later) */
namespace Service {
	enum Type {
		GameStateManager, ItemManager, InputManager,
		CharacterManager, SDL_Renderer, LevelManager,
		CollisionHelper, Config
	};
};

/* allows objects like game states to have a central place to
 * request things like InputManager, CollisionHelper etc from.
 * This makes them easier to work with and lets us keep all the
 * objects that should exist for the whole life of the game
 * (like the aforementioned managers) all in one place. 
 *
 * When these objects are handled like this we call them services
 * (for want of a better word). SDL_Renderer is handled differently
 * as it is a struct, not an object.
 */
class Services {

public:
	//constructor
	Services(SDL_Renderer* renderer);
	//destructor, should delete all services in use
	~Services();

	/* allow another object to request any type of service object
	 * by passing in one of the service types in the enum above. 
	 * The caller will receive a ServiceBase* which it must cast
	 * to the type of object it requested. See most of the game
	 * state class constructors to see how that is done. */
	ServiceBase* GetService(Service::Type serviceType);
	
	//allow access to the renderer
	SDL_Renderer* GetSDL_Renderer() { return renderer; }

private:
	//container of 'service' objects, plus SDL_Renderer
	std::map<Service::Type, ServiceBase*> services;
	SDL_Renderer* renderer;
};

#endif