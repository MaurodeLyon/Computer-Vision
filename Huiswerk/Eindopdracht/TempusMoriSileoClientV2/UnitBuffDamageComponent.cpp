#include "stdafx.h"
#include "UnitBuffDamageComponent.h"


UnitBuffDamageComponent::UnitBuffDamageComponent(Entity* entity, int attack) : attack(attack)
{
	for (auto component : entity->getComponents())
	{
		AttackComponent* comp = dynamic_cast<AttackComponent*>(component);
		if (comp != nullptr)
		{
			defaultAttack = comp->returnDamage();
			comp->setDamage(defaultAttack - attack);
		}
	}
	alive = true;
}


UnitBuffDamageComponent::~UnitBuffDamageComponent()
{
}

void UnitBuffDamageComponent::resetToDefault(Entity* entity)
{
	for (auto component : entity->getComponents())
	{
		AttackComponent* comp = dynamic_cast<AttackComponent*>(component);
		if (comp != nullptr)
		{
			comp->setDamage(defaultAttack);
		}
	}
	alive = false;
}
