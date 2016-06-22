#pragma once
#include "NPCComponent.h"

class CollisionComponent : public Component
{
public:
	CollisionComponent(float radius) { this->collisionRadius = radius; }
	~CollisionComponent() {};

	void update(Entity& entity) override;

	bool collisionIntersect(float x, float y, float radius);
	bool collisionIntersect(CollisionComponent otherCollisionBox);

	NPCComponent::Point2D getCollisionLocation() { return collisionBoxLocation; }
	float getCollisionRadius() { return collisionRadius; }
private:
	NPCComponent::Point2D collisionBoxLocation;
	float collisionRadius;

	float distance(float x, float z);
};

