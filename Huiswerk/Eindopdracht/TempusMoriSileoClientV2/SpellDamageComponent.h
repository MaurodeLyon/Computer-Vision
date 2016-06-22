#pragma once
class SpellDamageComponent : public SpellAreaComponent
{
public:
	SpellDamageComponent(float sizeX, float sizeZ, int damage);
	void action(Entity* entity) override;

private:
	int damage;
};

