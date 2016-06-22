#include "stdafx.h"
#include "UnitSlowSpeedComponent.h"


UnitSlowSpeedComponent::UnitSlowSpeedComponent(Entity* entity, float speed) : speed(speed)
{
	for (auto component : entity->getComponents())
	{
		NPCComponent* comp = dynamic_cast<NPCComponent*>(component);
		if (comp != nullptr)
		{
			defaultSpeed = comp->getSpeed();
			if (defaultSpeed - speed <= 0) comp->setSpeed(0);
			else comp->setSpeed(defaultSpeed - speed);
		}
	}
	alive = true;
}

UnitSlowSpeedComponent::~UnitSlowSpeedComponent()
{
}

void UnitSlowSpeedComponent::resetToDefault(Entity* entity)
{
	for (auto component : entity->getComponents())
	{
		NPCComponent* comp = dynamic_cast<NPCComponent*>(component);
		if (comp != nullptr)
		{
			comp->setSpeed(defaultSpeed);
		}
	}
	alive = false;
}
