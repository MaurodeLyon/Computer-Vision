#include "stdafx.h"

void Entity::addComponent(Component* component)
{
	components.push_back(component);
};

void Entity::update()
{
	for each(Component* c in components)
	{
		c->update(*this);
	}
}

void Entity::render()
{
	for each(Component* c in components)
	{
		c->render();
	}
}
