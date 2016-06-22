#include "stdafx.h"
#include "SpawnerComponent.h"

extern std::vector<Entity*> entitiesToAdd;
extern std::vector<pair<string, ObjModel*>> objectLibrary;

void SpawnerComponent::update(Entity& entity)
{
	if (timer <= 0)
	{

		Entity * astroid = new Entity((rand() % 500) - 250, (rand() % 500) - 250, entity.z);
		astroid->addComponent(new ObjModelComponent(objectLibrary[11].second));
		astroid->addComponent(new AstroidComponent((rand() % 4) + 1));
		astroid->addComponent(new CollisionComponent(5));
		entitiesToAdd.push_back(astroid);
		timer = rand() % 10;
	}
	timer--;
}
