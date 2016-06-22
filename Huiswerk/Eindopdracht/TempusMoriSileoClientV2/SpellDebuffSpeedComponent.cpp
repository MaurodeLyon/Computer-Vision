#include "stdafx.h"
#include "SpellDebuffSpeedComponent.h"
#include "UnitSlowSpeedComponent.h"

extern vector<Entity*> entities;

SpellDebuffSpeedComponent::SpellDebuffSpeedComponent(float sizeX, float sizeZ, int counter, float loweredSpeed): SpellAreaComponent(sizeX, sizeZ), counter(counter), loweredSpeed(loweredSpeed)
{
}

void SpellDebuffSpeedComponent::action(Entity* entity)
{
	if(tick == counter - 2)
	{
		for(auto e : entities)
		{
			for (auto component : e->getComponents())
			{
				UnitSlowSpeedComponent* comp = dynamic_cast<UnitSlowSpeedComponent*>(component);
				if (comp != nullptr)
				{
					comp->resetToDefault(e);
				}
			}
		}
	}
	else
	{
		for (auto component : entity->getComponents())
		{
			UnitSlowSpeedComponent* comp = dynamic_cast<UnitSlowSpeedComponent*>(component);
			if (comp != nullptr)
			{
				if(comp->alive)
				hasBuff = true;
			}
		}
		if(!hasBuff)
		{
			entity->addComponent(new UnitSlowSpeedComponent(entity, loweredSpeed));
			hasBuff = false;
		}

	}
}


