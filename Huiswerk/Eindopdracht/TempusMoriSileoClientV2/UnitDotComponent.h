#pragma once
class UnitDotComponent : public Component
{
public:
	UnitDotComponent(Entity* entity, int damage, int counter);
	~UnitDotComponent();


	void update(Entity& entity) override;

private:
	int damage;
	int counter;
	int tick;
};

