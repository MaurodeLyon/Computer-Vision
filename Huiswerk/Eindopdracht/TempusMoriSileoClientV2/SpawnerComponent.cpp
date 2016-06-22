#include "stdafx.h"
#include "SpawnerComponent.h"

extern std::vector<Entity*> entitiesToAdd;
extern std::vector<pair<string, ObjModel*>> objectLibrary;

void SpawnerComponent::update(Entity& entity)
{
	if (timer <= 0)
	{

		Entity * astroid = new Entity(rand() % 100, rand() % 100, entity.z);
		astroid->addComponent(new ObjModelComponent(objectLibrary[10].second));
		astroid->addComponent(new AstroidComponent((rand() % 4)+1));
		entitiesToAdd.push_back(astroid);
		timer = rand() % 10;
	}

	timer--;
}
