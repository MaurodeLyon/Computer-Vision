#include "stdafx.h"
#include "SpellResurrectionComponent.h"

extern std::vector<Entity*> entitiesToAdd;
extern std::vector<pair<string, ObjModel*>> objectLibrary;

SpellResurrectionComponent::SpellResurrectionComponent(PlayerComponent* player)
{
	Entity *unit = new Entity(-10, 0, 0);
	unit->addComponent(new ObjModelComponent(objectLibrary[6].second));
	unit->addComponent(new NPCComponent(2, 0, player->getPlayer(), true, 5));
	unit->addComponent(new CollisionComponent(10));
	unit->addComponent(new AttackComponent(5.0f, 1, 10));
	unit->addComponent(new UnitComponent(10, 1));
	entitiesToAdd.push_back(unit);

	Entity *unit2 = new Entity(0, 0, 0);
	unit2->addComponent(new ObjModelComponent(objectLibrary[6].second));
	unit2->addComponent(new NPCComponent(2, 1, player->getPlayer(), true, 5));
	unit2->addComponent(new CollisionComponent(10));
	unit2->addComponent(new AttackComponent(5.0f, 1, 10));
	unit2->addComponent(new UnitComponent(10, 1));
	entitiesToAdd.push_back(unit2);

	Entity *unit3 = new Entity(10, 0, 0);
	unit3->addComponent(new ObjModelComponent(objectLibrary[6].second));
	unit3->addComponent(new NPCComponent(2, 2, player->getPlayer(), true, 5));
	unit3->addComponent(new CollisionComponent(10));
	unit3->addComponent(new AttackComponent(5.0f, 1, 10));
	unit3->addComponent(new UnitComponent(10, 1));
	entitiesToAdd.push_back(unit3);
}


SpellResurrectionComponent::~SpellResurrectionComponent()
{
}
