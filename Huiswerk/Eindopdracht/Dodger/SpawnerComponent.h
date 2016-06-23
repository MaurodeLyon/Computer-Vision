#pragma once
class SpawnerComponent : public Component
{
public:
	SpawnerComponent() : timer(0) {};
	~SpawnerComponent(){};

	void update(Entity& entity) override;
private:
	int timer;
};

