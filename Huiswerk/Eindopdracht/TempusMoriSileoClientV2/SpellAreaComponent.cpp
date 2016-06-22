#include "stdafx.h"
#include "SpellAreaComponent.h"

extern vector<Entity*> entities;

SpellAreaComponent::SpellAreaComponent(float sizeX, float sizeZ) : sizeX(sizeX), sizeZ(sizeZ)
{
	tick = 0;
}


SpellAreaComponent::~SpellAreaComponent()
{
}

void SpellAreaComponent::update(Entity& entity)
{
	checkCollision(entity);
}

void SpellAreaComponent::checkCollision(Entity& entity)
{
	for(auto mob : entities)
	{
		for(auto component : mob->getComponents())
		{
			if (dynamic_cast<const CollisionComponent*>(component) != nullptr)
			{
				if (mob->x < entity.x + sizeX / 2 && mob->x > entity.x - sizeX / 2 && mob->z < entity.z + sizeZ / 2 && mob->z > entity.z - sizeZ / 2 && entity.y <= 1 && mob != &entity)
				{
					action(mob);
				}
			}
		}
	}
	tick++;
}
