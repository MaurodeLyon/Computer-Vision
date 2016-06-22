#include "stdafx.h"
#include "ShipComponent.h"

extern int x;
extern int y;

void ShipComponent::update(Entity& entity)
{
	entity.x = x;
	entity.y = y;
}