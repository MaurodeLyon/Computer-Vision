#include "stdafx.h"
#include "Engine.h"

Audio audio;
std::vector<Entity*> entities;
std::vector<Entity*> entitiesToAdd;
extern std::vector<pair<string, ObjModel*>> objectLibrary;

void Engine::init_world()
{
	entities.clear();
	//init skybox
	auto * skyBox_entity = new Entity();
	skyBox_entity->addComponent(new ObjModelComponent(objectLibrary[1].second));
	//skyBox_entity->addComponent(new AudioComponent("res/music/background.mp3", true, true, 1.0f));
	entities.push_back(skyBox_entity);

	auto * ship = new Entity();
	ship->addComponent(new ObjModelComponent(objectLibrary[3].second));
	ship->addComponent(new ShipComponent());
	ship->addComponent(new CollisionComponent(5));
	entities.push_back(ship);
	
	auto * spawner = new Entity(0,0,-250);
	spawner->addComponent(new ObjModelComponent(objectLibrary[4].second));
	spawner->addComponent(new SpawnerComponent());
	entities.push_back(spawner);
}

Engine::Engine()
{
	init_world();

}

