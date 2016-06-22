#include "stdafx.h"
#include "SpellBuffComponent.h"


SpellBuffComponent::SpellBuffComponent(float sizeX, float sizeZ, int counter) : SpellAreaComponent(sizeX, sizeZ), counter(counter)
{
	tick = 0;
}

void SpellBuffComponent::action(Entity* entity)
{
	for (auto component : entity->getComponents())
	{
		NPCComponent* comp = dynamic_cast<NPCComponent*>(component);
		if (comp != nullptr)
		{
			if (firstTick)
			{
				standardSpeed = comp->getSpeed();
				firstTick = false;
			}
			comp->setSpeed(standardSpeed + 1.5f);
			if (tick >= (counter - 2)) comp->setSpeed(standardSpeed);
		}
	}
}


