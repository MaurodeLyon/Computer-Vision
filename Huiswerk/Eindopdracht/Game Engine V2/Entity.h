#pragma once
class Entity
{
public:
	unsigned int ID;
	int velocity;
	int x, y, z;

	Entity() :velocity(0), x(0), y(0), z(0) {
	
	}
	~Entity() {}
	void addComponent(Component* component);
	void update();
	void render();
private:
	std::vector<Component*> components;
};

