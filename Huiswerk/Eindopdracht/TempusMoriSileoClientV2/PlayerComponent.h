#pragma once

class PlayerComponent : public Component
{
public:
	PlayerComponent(bool isPlayer1);
	~PlayerComponent() {};

	virtual void update(Entity& entity);

	void lowerHealth(int damage);
	void lowerEnergy(int energy);

	void setUndead(), setHuman(), setMage(), setSanic();

	void changeHealth(int health);
	void changeEnergy(int energy);
	void changeMaxHealth(int health);

	bool getPlayer() { return player; }
	double getHealth() { return health; }
	double getEnergy() { return energy; }
	int getFaction() { return faction; };
private:
	double health, maxHealth;
	double energy, maxEnergy;
	enum Faction { Undead, Human, Mage, Sanic } faction;
	bool player, loadTextures;
};

