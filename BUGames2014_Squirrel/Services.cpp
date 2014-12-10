#include "Services.h"
#include "GamestateManager.h"
#include "InputManager.h"
#include "ItemManager.h"
#include "CharacterManager.h"
#include "LevelManager.h"
#include "CollisionHelper.h"
#include "Config.h"

Services::Services(SDL_Renderer* renderer) {
	
	//store incoming SDL_Renderer struct
	this->renderer = renderer;

	/* here we create objects to represent all the different
	 * types of 'service' the engine uses. These should really
	 * be interfaces, but that's getting ahead of ourselves a bit. */

	//services that don't depend on any others
	services[Service::CollisionHelper] = new CollisionHelper();
	services[Service::GameStateManager] = new GamestateManager();
	services[Service::InputManager] = new InputManager();
	services[Service::Config] = new Config();
	
	//services that do depend on others
	services[Service::LevelManager] = new LevelManager(this);
	services[Service::CharacterManager] = new CharacterManager(this);
	services[Service::ItemManager] = new ItemManager(this);
}

Services::~Services() {

	/* destroy all the services, should only be called 
	 * when the game is being quit */

	delete services[Service::CollisionHelper];
	delete services[Service::GameStateManager];
	delete services[Service::InputManager];
	delete services[Service::Config];
	delete services[Service::LevelManager];
	delete services[Service::CharacterManager];
	delete services[Service::ItemManager];
}

//return whatever type of service to the caller as a ServiceBase*
ServiceBase* Services::GetService(Service::Type serviceType) {
	return services[serviceType];
}