#pragma once
class ShipComponent : public Component
{
public:
	ShipComponent() : health(3) {};
	~ShipComponent() {};
	void update(Entity& entity) override;
	int getHealth() const { return health; }
	void setHealth(int health) { this->health = health; }
private:
	int health;

};

