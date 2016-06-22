#pragma once
class SpellStaticComponent : public Component
{
public:
	SpellStaticComponent(int counter);
	~SpellStaticComponent();

	void update(Entity& entity) override;

private:
	int counter;
	int currentTick;
};

