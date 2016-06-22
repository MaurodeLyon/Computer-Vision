#include "stdafx.h"
#include "SpellBuffDamageComponent.h"
#include "UnitSlowSpeedComponent.h"
#include "UnitBuffDamageComponent.h"

extern vector<Entity*> entities;

SpellBuffDamageComponent::SpellBuffDamageComponent(float sizeX, float sizeZ, int counter, float extraAttack) : SpellAreaComponent(sizeX, sizeZ), counter(counter), extraAttack(extraAttack)
{
}


SpellBuffDamageComponent::~SpellBuffDamageComponent()
{
}

void SpellBuffDamageComponent::action(Entity* entity)
{
	if (tick == counter - 2)
	{
		for (auto e : entities)
		{
			for (auto component : e->getComponents())
			{
				UnitBuffDamageComponent* comp = dynamic_cast<UnitBuffDamageComponent*>(component);
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
			UnitBuffDamageComponent* comp = dynamic_cast<UnitBuffDamageComponent*>(component);
			if (comp != nullptr)
			{
				if (comp->alive)
					hasBuff = true;
			}
		}
		if (!hasBuff)
		{
			entity->addComponent(new UnitBuffDamageComponent(entity, extraAttack));
			hasBuff = false;
		}

	}
}
