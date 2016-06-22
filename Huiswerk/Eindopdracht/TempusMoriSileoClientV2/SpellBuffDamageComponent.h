#pragma once
class SpellBuffDamageComponent : public SpellAreaComponent
{
public:
	SpellBuffDamageComponent(float sizeX, float sizeZ, int counter, float addedSpeed);
	~SpellBuffDamageComponent();

	void action(Entity* entity) override;

private:
	bool firstTick;
	float extraAttack;
	int counter;
	bool hasBuff;
};

