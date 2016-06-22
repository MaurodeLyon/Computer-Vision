#pragma once
#include "NPCComponent.h"
#include "Audio.h"

class AttackComponent : public Component
{
public:
	int damage;

	AttackComponent(float radius, int damage, float attckRange) { attackRadius = radius; this->damage = damage; attRange = attckRange; hasAggro = false; isAttacking = false; }
	~AttackComponent() {};

	virtual void update(Entity& entity);
	virtual void render(Entity&) {};

	bool attackIntersect(float, float);
	void attackUpdateLocation(int, int);
	int returnDamage() const{return damage;}
	void setDamage(int damage) {this->damage = damage;}
	bool hasAggro;
	bool isAttacking;

private:
	NPCComponent::Point2D attackBoxLocation;
	float attackRadius;
	float attRange;
	float distance;

	float attackDistance(float, float);
};
