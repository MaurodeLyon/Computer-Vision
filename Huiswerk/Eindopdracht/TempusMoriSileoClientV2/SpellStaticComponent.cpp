#include "stdafx.h"
#include "SpellStaticComponent.h"


SpellStaticComponent::SpellStaticComponent(int counter) : counter(counter)
{
	currentTick = 0;
}


SpellStaticComponent::~SpellStaticComponent()
{
}

void SpellStaticComponent::update(Entity& entity)
{
	if (currentTick > counter)
	{
		entity.alive = false;
	}
	else
	{
		currentTick++;
	}
}
