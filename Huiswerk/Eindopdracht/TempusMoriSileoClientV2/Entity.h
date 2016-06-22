#pragma once


class Entity
{
public:
	std::vector<Component*> components;
	float x, y, z;
	bool alive = true;
	Entity() : x(0), y(0), z(0) {}
	Entity(float x, float y, float z) : x(x), y(y), z(z) {}
	~Entity() {}

	void update();
	void render();

	void addComponent(Component* component);
	std::vector<Component*> getComponents() { return components; }
};

