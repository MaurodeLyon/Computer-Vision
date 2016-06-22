#include "stdafx.h"
#include "TrainMoveComponent.h"

extern std::vector<Entity*> entities;
TrainMoveComponent::TrainMoveComponent(float targetX, float targetY, float targetZ, float speed) : targetPos(targetX, targetY, targetZ), speed(speed)
{
	for (auto mob : entities)
	{
		for (auto component : mob->getComponents())
		{
			if (dynamic_cast<const AudioComponent*>(component) != nullptr)
			{
				auto c = dynamic_cast<const AudioComponent*>(component);
				c->engine->stopAllSounds();
			}
		}
	}
}


TrainMoveComponent::~TrainMoveComponent()
{
}

void TrainMoveComponent::update(Entity& entity)
{
	move(entity);
}

void TrainMoveComponent::move(Entity& entity)
{
	if (entity.x > targetPos.x - 1 && entity.x < targetPos.x + 1 && entity.y > targetPos.y - 1 && entity.y < targetPos.y + 1 && entity.z > targetPos.z - 1 && entity.z < targetPos.z + 1)
	{
		for (auto mob : entities)
		{
			for (auto component : mob->getComponents())
			{
				if (dynamic_cast<const AudioComponent*>(component) != nullptr)
				{
					auto c = dynamic_cast<const AudioComponent*>(component);
					c->engine->stopAllSounds();
				}
			}
		}
		auto * skyBox_entity = new Entity(0, 0, 0);
		skyBox_entity->addComponent(new AudioComponent("res/music/sanic.mp3", true, true, 0.2f));
		entities.push_back(skyBox_entity);
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