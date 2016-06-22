#pragma once

class UserInterfaceComponent : public Component
{
public:
	UserInterfaceComponent();
	~UserInterfaceComponent() {};

	virtual void render(Entity& entity);

	void glutBitmapString(std::string str, int x, int y);
	void loadTextures(string pictureName, bool unitPicture);
	void nextUnit();
	void nextSpell();
	void undeadTextures();
	void wizardsTextures();
	void humanTextures();
	void setHealth(int health) { this->health = health; }
	void setEnemyHealth(int enemyHealth) { this->enemyHealth = enemyHealth; }

	void setEnergy(int energy) { this->energy = energy; }
	void setMaxEnergy(int maxEnergy) { this->maxEnergy = maxEnergy; }

	void setMaxEnemyHealth(double maxEnemyHealth) { this->maxEnemyHealth = maxEnemyHealth; };
	void setMaxHealth(double maxHealth) { this->maxHealth = maxHealth; };
private:
	double maxHealth, maxEnemyHealth, maxEnergy;
	int health, enemyHealth, energy;
	int unit;
	int spell;

	GLuint unitSelect;
	vector<pair<string, GLuint>> unitPictures;
	vector<pair<string, GLuint>> spellPictures;
};

