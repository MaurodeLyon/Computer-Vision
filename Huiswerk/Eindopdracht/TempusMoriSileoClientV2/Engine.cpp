#include "stdafx.h"
#include "Engine.h"

Audio audio;
std::vector<Entity*> entities;
std::vector<Entity*> entitiesToAdd;
extern std::vector<pair<string, ObjModel*>> objectLibrary;

void Engine::init_world(int faction)
{
	entities.clear();
	//init skybox
	auto * skyBox_entity = new Entity(0, 0, 0);
	skyBox_entity->addComponent(new ObjModelComponent(objectLibrary[1].second));
	skyBox_entity->addComponent(new AudioComponent("res/music/background.mp3", true, true, 1.0f));
	entities.push_back(skyBox_entity);

	//init map
	auto * map_entity = new Entity();
	map_entity->addComponent(new ObjModelComponent(objectLibrary[0].second));
	entities.push_back(map_entity);

	//init castles

	//Castle 1
	auto * castleP1_entity = new Entity(0, 0, 60);
	auto * player1 = new PlayerComponent(true);
	if (faction == 0)		player1->setUndead();
	else if (faction == 1)		player1->setHuman();
	else if (faction == 2)		player1->setMage();
	castleP1_entity->addComponent(new ObjModelComponent(objectLibrary[2].second, 0, 3.5f));
	castleP1_entity->addComponent(new UnitSpellsFactory(player1, player1->getFaction()));
	castleP1_entity->addComponent(player1);
	entities.push_back(castleP1_entity);


	//Castle 2	
	auto * castleP2_entity = new Entity(2, 0, -60);
	auto * player2 = new PlayerComponent(false);
	player2->setUndead();

	castleP2_entity->addComponent(new ObjModelComponent(objectLibrary[2].second, 0, 3.5f));
	castleP2_entity->addComponent(new UnitSpellsFactory(player2, player2->getFaction()));
	castleP2_entity->addComponent(player2);
	entities.push_back(castleP2_entity);
}

void Engine::init_Menu()
{
	auto * menuEntity = new Entity(0, 0, 0);
	menuEntity->addComponent(new MenuComponent(this));
	entities.push_back(menuEntity);
}

void Engine::init_Interface()
{
	auto * interfaceEntity = new Entity(0, 0, 0);
	interfaceEntity->addComponent(new UserInterfaceComponent());
	entities.push_back(interfaceEntity);

	auto * rightCursor = new Entity(0, 10, 0);
	rightCursor->addComponent(new ObjModelComponent(objectLibrary[4].second));
	rightCursor->addComponent(new CursorComponent(true));
	entities.push_back(rightCursor);

	auto * leftCursor = new Entity(0, 10, 0);
	leftCursor->addComponent(new ObjModelComponent(objectLibrary[3].second));
	leftCursor->addComponent(new CursorComponent(false));
	entities.push_back(leftCursor);
}

Engine::Engine()
{
	//laad wereld
	
}

