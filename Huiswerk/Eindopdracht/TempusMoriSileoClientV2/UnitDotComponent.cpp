#include "stdafx.h"
#include "UnitDotComponent.h"


UnitDotComponent::UnitDotComponent(Entity* entity, int damage, int counter) : damage(damage), counter(counter)
{
	int tick = 0;
}

UnitDotComponent::~UnitDotComponent()
{
}

void UnitDotComponent::update(Entity& entity)
{
	if(tick >= 20)
	{
		for (auto component : entity.getComponents())
		{
			UnitComponent* comp = dynamic_cast<UnitComponent*>(component);
			if (comp != nullptr)
			{
				comp->removeHP(damage);
			}
		}
		tick = 0;
	}
	tick++;
}
