#pragma once
class Entity;
class Component
{
public:
	virtual void update(Entity& entity){};
	virtual void render(Entity& entity){};
};