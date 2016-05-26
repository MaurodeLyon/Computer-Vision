#pragma once

class Entity;

class Component
{
public:
	virtual void update(Entity& entity)
	{
		std::cout << "update: component" << std::endl;
	}
};

