#pragma once
class SpellBuffComponent : public SpellAreaComponent
{
public:
	SpellBuffComponent(float sizeX, float sizeZ, int counter);
	void action(Entity* entity) override;

private:
	bool firstTick = true;
	float standardSpeed;
	int counter;
};

