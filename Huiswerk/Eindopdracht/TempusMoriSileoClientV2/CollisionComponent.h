#pragma once

class CollisionComponent : public Component
{
public:
	CollisionComponent(float radius) { this->collisionRadius = radius; }
	~CollisionComponent() {};

	void update(Entity& entity) override;

	bool collisionIntersect(float x, float y, float z, float radius) const;
	bool collisionIntersect(CollisionComponent otherCollisionBox) const;


	float getCollisionRadius() const { return collisionRadius; }
private:
	float position[3];
	float collisionRadius;
	float distance(float x, float y, float z) const;

};

