#include "stdafx.h"
#include "AstroidComponent.h"

void AstroidComponent::update(Entity& entity)
{
	entity.z += speed;
}
