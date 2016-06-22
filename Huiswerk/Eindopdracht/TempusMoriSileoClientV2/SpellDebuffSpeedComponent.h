#pragma once
class SpellDebuffSpeedComponent : public SpellAreaComponent
{
public:
	SpellDebuffSpeedComponent(float sizeX, float sizeZ, int counter, float addedSpeed);
	void action(Entity* entity) override;

private:
	bool firstTick;
	float loweredSpeed;
	int counter;
	bool hasBuff;
};

