#include "stdafx.h"
#include "PlayerComponent.h"

extern std::vector<Entity*> entities;
extern int ticks;

PlayerComponent::PlayerComponent(bool isPlayer1)
{
	this->player = isPlayer1;
	loadTextures = true;
}

void PlayerComponent::update(Entity & e)
{
	for each (auto entity in entities)
	{
		for each(auto component in entity->getComponents())
		{
			if (dynamic_cast<const UserInterfaceComponent*>(component) != nullptr)
			{
				UserInterfaceComponent* interface = (UserInterfaceComponent*)component;
				if (player) {
					interface->setMaxHealth(maxHealth);
					interface->setHealth(health);
					interface->setMaxEnergy(maxEnergy);
					interface->setEnergy(energy);
					if (loadTextures)
					{
						if (faction == 0) { interface->undeadTextures(); }
						else if (faction == 1) { interface->humanTextures(); }
						else if (faction == 2) { interface->wizardsTextures(); }
						loadTextures = false;
					}
				}
				else if (!player)
				{
					interface->setMaxEnemyHealth(maxHealth);
					interface->setEnemyHealth(health);
				}
			}
		}
	}

	if (ticks == 59 && energy < maxEnergy)
	{
		//energy += 50;
		if (energy > maxEnergy) energy = maxEnergy;
		std::cout << player << "- energy is: " << energy << std::endl;
	}

	if (health <= 0)
	{
		e.alive = false;
		health = 0;
	}
}

void PlayerComponent::changeHealth(int health)
{
	this->health = health;
}

void PlayerComponent::changeEnergy(int energy)
{
	if (energy > 0 && energy <= 500)
	{
		this->energy = energy;
	}
	else if (energy <= 0)
	{
		this->energy = energy;
		cout << "No energy left //PlayerComponent" << endl;
	}
	else
	{
		cout << "energy must be between 0 and maxEnergy //PlayerComponent" << endl;
	}
}

void PlayerComponent::changeMaxHealth(int max) {
	this->maxHealth = max;
}

void PlayerComponent::lowerHealth(int damage)
{
	health = health - damage;
	changeHealth(health);
}

void PlayerComponent::lowerEnergy(int energy)
{
	auto newHealth = this->energy;
	newHealth = newHealth - energy;
	changeEnergy(newHealth);
}

void PlayerComponent::setUndead()
{
	faction = Undead;
	maxHealth = 50;
	maxEnergy = 100;
	health = 50;
	energy = 0;
	cout << maxHealth << "UNDEAD MAXHEALTH" << endl;
}

void PlayerComponent::setHuman()
{
	faction = Human;
	maxHealth = 50;
	maxEnergy = 200;
	health = 50;
	energy = 0;
	cout << maxHealth << "HUMAN MAXHEALTH" << endl;
}

void PlayerComponent::setMage()
{
	faction = Mage;
	maxHealth = 50;
	maxEnergy = 300;
	health = 50;
	energy = 0;
	cout << maxHealth << "MAGE MAXHEALTH" << endl;
}
void PlayerComponent::setSanic()
{
	faction = Sanic;
	maxHealth = 1000;
	maxEnergy = 1000;
	health = 1000;
	energy = 0;
	cout << maxHealth << "SANIC MAXHEALTH" << endl;
}