#include "stdafx.h"
#include "SpellDamageComponent.h"


SpellDamageComponent::SpellDamageComponent(float sizeX, float sizeZ, int damage): SpellAreaComponent(sizeX, sizeZ), damage(damage)
{
}

void SpellDamageComponent::action(Entity* entity)
{
	for (auto component : entity->getComponents())
	{
		UnitComponent* comp = dynamic_cast<UnitComponent*>(component);
		if (comp != nullptr)
		{
			comp->removeHP(damage);
		}
	}
}
