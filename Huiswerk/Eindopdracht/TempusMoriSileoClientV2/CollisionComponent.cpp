#include "stdafx.h"
#include "CollisionComponent.h"

extern std::vector<Entity*> entities;

void CollisionComponent::update(Entity& entity)
{
	position[0] = entity.x;
	position[1] = entity.y;
	position[2] = entity.z;

	for each(Component * shipComponent in entity.getComponents())
		if (dynamic_cast<const ShipComponent*>(shipComponent) != nullptr) //entity is a ship		
			for each(Component * collisionComponent in entity.getComponents())
				if (dynamic_cast<const CollisionComponent*>(collisionComponent) != nullptr) // get collisioncomponent of ship
				{
					CollisionComponent* shipCollision = (CollisionComponent*)collisionComponent;
					for each (Entity *other_entity in entities)
						if (&entity != other_entity)
							for each(Component * astroidComponent in other_entity->getComponents())
								if (dynamic_cast<const AstroidComponent*>(astroidComponent) != nullptr)	//other entity is a astroid
									for each(Component * component in other_entity->getComponents())
										if (dynamic_cast<const CollisionComponent*>(component) != nullptr) // get astroid collision component
										{
											CollisionComponent* astroidCollision = (CollisionComponent*)component;
											float distance = (float)sqrt((position[0] - other_entity->x) * (position[0] - other_entity->x) + (position[1] - other_entity->y) * (position[1] - other_entity->y) + (position[2] - other_entity->z) * (position[2] - other_entity->z));
											float radius = shipCollision->getCollisionRadius() + astroidCollision->getCollisionRadius();
											bool collision = distance < radius;
											if (collision)
											{
												cout << this->distance(astroidCollision->position[0], astroidCollision->position[1], astroidCollision->position[2]) << endl;
												//collision with astroid
												other_entity->alive = false;
											}
										}
				}
}

/*check if 2 circles intersect*/
bool CollisionComponent::collisionIntersect(float x, float y, float z, float radius) const
{
	if (distance(x, y, z) <= collisionRadius + radius) return true;
	return false;
}

bool CollisionComponent::collisionIntersect(CollisionComponent otherCollisionBox) const
{
	float afstand = distance(otherCollisionBox.position[0], otherCollisionBox.position[1], otherCollisionBox.position[2]);
	float radius = collisionRadius + otherCollisionBox.getCollisionRadius();
	if (afstand <= radius) return true;
	return false;
}

/*Distance between circle centers*/
float CollisionComponent::distance(float x, float y, float z) const
{
	float deltaX = position[0] - x;
	float deltaY = position[1] - y;
	float deltaZ = position[2] - z;
	float distance = (float)sqrt(deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ);
	return distance;
}