#include "stdafx.h"
#include "SpellDotComponent.h"
#include "UnitDotComponent.h"


SpellDotComponent::SpellDotComponent(Entity* entity, float sizeX, float sizeZ, int counter, float dot) : SpellAreaComponent(sizeX, sizeZ), counter(counter), dot(dot)
{
	//entity->addComponent(new UnitDotComponent(entity, dot, counter));
}


SpellDotComponent::~SpellDotComponent()
{
}

void SpellDotComponent::action(Entity* entity)
{
	for (auto component : entity->getComponents())
	{
		UnitDotComponent* comp = dynamic_cast<UnitDotComponent*>(component);
		if (comp != nullptr)
		{
			hasDot = true;
		}
	}
	if (!hasDot)
	{
		entity->addComponent(new UnitDotComponent(entity, dot, counter));
		hasDot = false;
	}
}
