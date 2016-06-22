#pragma once
class UnitBuffDamageComponent : public Component
{
public:
	bool alive;

	UnitBuffDamageComponent(Entity* entity, int attack);
	~UnitBuffDamageComponent();

	void resetToDefault(Entity* entity);

private:
	float defaultAttack;
	float attack;
};

