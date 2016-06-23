#pragma once
class ShipComponent : public Component
{
public:
	ShipComponent() : health(3), rotation(0) {};
	~ShipComponent() {};

	void update(Entity& entity) override;
	void render(Entity& entity) override;


	int getHealth() const { return health; }
	void setHealth(int health) { this->health = health; }
private:
	int health;
	float rotation;

};

