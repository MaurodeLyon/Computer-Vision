#include "stdafx.h"
#include "SpellMoveComponent.h"
#include "Entity.h"


SpellMoveComponent::SpellMoveComponent(float targetX, float targetY, float targetZ, float speed) : targetPos(targetX, targetY, targetZ), speed(speed)
{

}

SpellMoveComponent::~SpellMoveComponent()
{
}

void SpellMoveComponent::update(Entity& entity)
{
	move(entity);
}

void SpellMoveComponent::move(Entity& entity)
{
	if (entity.x > targetPos.x - 1 && entity.x < targetPos.x + 1 && entity.y > targetPos.y - 1 && entity.y < targetPos.y + 1 && entity.z > targetPos.z - 1 && entity.z < targetPos.z + 1)
	{
		entity.alive = false;
	}
	else
	{
		distance.x = entity.x - targetPos.x;
		distance.y = entity.y - targetPos.y;
		distance.z = entity.z - targetPos.z;

		float hyp = sqrt(distance.x*distance.x + distance.y*distance.y + distance.z * distance.z);
		distance.x /= hyp;
		distance.y /= hyp;
		distance.z /= hyp;

		entity.x -= distance.x * speed;
		entity.y -= distance.y * speed;
		entity.z -= distance.z * speed;
	}
}


