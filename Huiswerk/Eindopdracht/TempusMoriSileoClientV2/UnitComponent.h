#pragma once
class UnitComponent : public Component
{
public:
	UnitComponent(int health, bool player) : maxHealth(health), health(health), player(player) {};
	~UnitComponent() {};

	void update(Entity& entity) {
		if (health < 1) entity.alive = false;
	};

	void removeHP(int damage) { health -= damage; };

	int getMaxHp() { return maxHealth; };
	int getHp() { return health; };
	int getPlayer() { return player; }
private:
	int maxHealth;
	int health;
	bool player;
};

