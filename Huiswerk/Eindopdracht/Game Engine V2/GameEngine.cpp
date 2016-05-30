#include "stdafx.h"
#include "GameEngine.h"


GameEngine::GameEngine()
{
}


GameEngine::~GameEngine()
{
}

void GameEngine::addEntity(Entity* e)
{
	for (int i = 0; i < entities.size(); i++)
	{
		e->ID = i + 1;
	}

	entities.push_back(e);
}

void GameEngine::removeEntity(int ID)
{
	std::vector<Entity*>::iterator it = entities.begin();
	for (; it != entities.end(); ) {
		Entity* e = *it._Ptr;
		if (e->ID == ID) {
			it = entities.erase(it);
		}
		else {
			++it;
		}
	}
}
