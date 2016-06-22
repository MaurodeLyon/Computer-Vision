#pragma once
class SpellDotComponent : public SpellAreaComponent
{
public:
	SpellDotComponent(Entity* entity, float sizeX, float sizeZ, int counter, float dot);
	~SpellDotComponent();

	void action(Entity* entity) override;

private:
	int counter;
	float dot;
	bool hasDot;
};

