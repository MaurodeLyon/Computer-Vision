#include "stdafx.h"
#include "ObjModelComponent.h"

void ObjModelComponent::render(Entity& entity)
{
	objModel->draw(entity, scale, rotation);
}
