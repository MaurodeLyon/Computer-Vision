#include "stdafx.h"
#include "CollisionComponent.h"

void CollisionComponent::update(Entity& entity)
{
	collisionBoxLocation.x = entity.x + 5;
	collisionBoxLocation.z = entity.z - 5;
}

/*check if 2 circles intersect*/
bool CollisionComponent::collisionIntersect(float x, float z, float radius)
{
	if (distance(x, z) <= collisionRadius + radius) return true;
	return false;
}

bool CollisionComponent::collisionIntersect(CollisionComponent otherCollisionBox)
{
	//cout << "collision distance: " << distance(otherCollisionBox.collisionBoxLocation.x, otherCollisionBox.collisionBoxLocation.z) << endl;
	if (distance(otherCollisionBox.collisionBoxLocation.x, otherCollisionBox.collisionBoxLocation.z) <= collisionRadius + otherCollisionBox.getCollisionRadius()) return true;
	return false;
}

/*Distance between circle centers*/
float CollisionComponent::distance(float x, float z)
{
	return sqrtf(powf(fabsf(collisionBoxLocation.x - x), 2) + powf(fabsf(collisionBoxLocation.z - z), 2));
}
