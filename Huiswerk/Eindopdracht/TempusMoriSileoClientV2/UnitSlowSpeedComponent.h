#pragma once
class UnitSlowSpeedComponent : public Component
{
public:
	bool alive;

	UnitSlowSpeedComponent(Entity* entity, float speed);
	~UnitSlowSpeedComponent();

	void resetToDefault(Entity* entity);

private:
	float defaultSpeed;
	float speed;
};

