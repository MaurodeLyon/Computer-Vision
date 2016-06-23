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
	skyBox_entity->addComponent(new ObjModelComponent(objectLibrary[0].second));
	skyBox_entity->addComponent(new AudioComponent("res/music/background.mp3", true, true, 1.0f));
	entities.push_back(skyBox_entity);

	auto * interface_entity = new Entity();
	interface_entity->addComponent(new UserInterfaceComponent());
	entities.push_back(interface_entity);

	auto * ship = new Entity();
	ship->addComponent(new ObjModelComponent(objectLibrary[1].second));
	ship->addComponent(new ShipComponent());
	ship->addComponent(new CollisionComponent(20));
	entities.push_back(ship);

	auto * spawner = new Entity(0, 0, -500);
	ObjModelComponent* model = new ObjModelComponent(objectLibrary[1].second);
	model->setRotation(180);
	model->setScale(0.5);

	spawner->addComponent(model);
	spawner->addComponent(new SpawnerComponent());
	entities.push_back(spawner);
}

Engine::Engine()
{
	init_world();

}

