#pragma once
class SpellAreaComponent : public Component
{
public:
	SpellAreaComponent(float sizeX, float sizeZ);
	~SpellAreaComponent();

	void update(Entity& entity) override;
	void checkCollision(Entity& entity);
	virtual void action(Entity* entity) = 0;

protected:
	float sizeX;
	float sizeZ;
	int tick;
};

