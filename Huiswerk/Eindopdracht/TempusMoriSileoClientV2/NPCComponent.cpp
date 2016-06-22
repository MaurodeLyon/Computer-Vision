#include "stdafx.h"
#include "NPCComponent.h"
#define	_USE_MATH_DEFINES

extern vector<Entity*> entities;

NPCComponent::NPCComponent(float speed, float lane, bool player, bool hasCollision, float collisionRadius)
{
	int random = rand() % 6;
	int check = (rand() & 2);
	//cout << "RANDOMMMM " << random << " " <<check << endl;
	if (check == 2)
		random = -random;
//	cout << "RANDOMMMM " << random << endl;
	position = { random * 20.0f,0 };
	currentWaypoint = 0;
	direction = 1;
	this->player = player;
	this->speed = speed;
	this->baseSpeed = speed;
	this->collisionRadius = collisionRadius;
	this->hasCollionEnabled = hasCollision;

	generateWaypoints(player, lane);
	destination = wayPoints[currentWaypoint];
	target = destination;
}

void NPCComponent::update(Entity& entity)
{
	//rotate toward target
	rotations();

	//move
	Point2D oldPosition = position;
	position = { float(position.x + speed * cos(direction)),float(position.z + speed * sin(direction)) };

	//check collision
	if (hasCollionEnabled)
		for each(Component * component in entity.getComponents())
		{
			if (dynamic_cast<const CollisionComponent*>(component) != nullptr)
				for each(Entity * other_entity in entities)
					if (other_entity != &entity)
						for each(Component * otherComponent in other_entity->getComponents())
							if (dynamic_cast<const CollisionComponent*>(otherComponent) != nullptr)
							{
								CollisionComponent* collisionComponent = (CollisionComponent*)component;
								CollisionComponent* otherCollisionComponent = (CollisionComponent*)otherComponent;
								if (collisionComponent->collisionIntersect(*otherCollisionComponent))direction += 0.2;
							}
		}

	//if necesary obtain newTarget
	newTarget(&entity);
	//update entity position
	entity.x = position.x;
	entity.z = position.z;

	//set the model correct
	for each(Component * c in entity.getComponents())
	{
		if (dynamic_cast<const ObjModelComponent*>(c) != nullptr)
		{
			ObjModelComponent* model = (ObjModelComponent*)c;
			model->setRotation(((-direction * 180) / PI)+90);
		}
	}
}

void NPCComponent::setTarget(Entity * entity)
{
	//set target x and z with enemy x and z
	target.x = entity->x;
	target.z = entity->z;
}

void NPCComponent::newTarget(Entity * entity) {
	AttackComponent* attComp;

	auto WPdistance = sqrtf(powf(fabsf(position.x - destination.x), 2) + powf(fabsf(position.z - destination.z), 2));
	for each(Component* com in entity->getComponents()) {
		if (dynamic_cast<AttackComponent*>(com) != nullptr) {
			attComp = (AttackComponent*)com;

			//Check waypoint distance
			if (WPdistance < 10) {										//if position is on target
				if (currentWaypoint < 4)currentWaypoint++;			//set target next waypoint
				else                                                //Damage castle
				{
					for each(Entity * other_entity in entities)
						for each(Component * component in other_entity->getComponents())
							if (dynamic_cast<const PlayerComponent*>(component) != nullptr)
								for each(Component * ownComp in entity->getComponents())
									if (dynamic_cast<const UnitComponent*>(ownComp) != nullptr)
									{
										PlayerComponent* player_component = (PlayerComponent*)component;
										UnitComponent* unit_component = (UnitComponent*)ownComp;
										if (player_component->getPlayer() != unit_component->getPlayer())
										{
											player_component->lowerHealth(5);
											entity->alive = false;
										}
									}
				}
				target = wayPoints[currentWaypoint];
				destination = wayPoints[currentWaypoint];
			}
			//Set target to waypoint & start walking again
			if (!attComp->hasAggro) {
				target.x = destination.x;
				target.z = destination.z;
				speed = baseSpeed;
			}
			//Is attacking
			else if (attComp->isAttacking) {
				speed = 0;
			}
		}
	}
}

void NPCComponent::rotations()
{
	direction += 0.01;

	Point2D difference = { target.x - position.x, target.z - position.z };

	double newRotation = atan2(difference.z, difference.x);
	double rotDifference = direction - newRotation;

	while (rotDifference > PI) {
		rotDifference -= 2 * PI;
	}

	while (rotDifference < -PI) {
		rotDifference += 2 * PI;
	}

	if (abs(rotDifference) < 0.1) {
		direction = newRotation;
	}
	else if (rotDifference < 0) {
		direction += 0.1;
	}
	else if (rotDifference > 0) {
		direction -= 0.1;
	}
}

void NPCComponent::generateWaypoints(bool player, int lane)
{
	cout << "generating waypoints for player " << player << "in lane: " << lane << endl;
	//Player 1
	if (player) {
		position.z = 235.0f;
		switch (lane)
		{
		case 0:
			wayPoints[0] = { -20.0f, 195.0f };
			wayPoints[1] = { -80.0f, 145.0f };
			wayPoints[2] = { -80.0f, -145.0f };
			wayPoints[3] = { -20.0f, -195.0f };
			wayPoints[4] = { 0.0f, -235.0f };
			break;
		case 1:
			wayPoints[0] = { 0.0f, 195.0f };
			wayPoints[1] = { 0.0f, 140.0f };
			wayPoints[2] = { 0.0f, 0.0f };
			wayPoints[3] = { 0.0f, -140.0f };
			wayPoints[4] = { 0.0f, -235.0f };
			break;
		case 2:
			wayPoints[0] = { 20.0f, 195.0f };
			wayPoints[1] = { 80.0f, 145.0f };
			wayPoints[2] = { 80.0f, -145.0f };
			wayPoints[3] = { 20.0f, -195.0f };
			wayPoints[4] = { 0.0f, -235.0f };
			break;
		}
	}
	//player 2
	else {
		position.z = -235.0f;
		switch (lane)
		{
		case 0:
			wayPoints[0] = { 20.0f, -195.0f };
			wayPoints[1] = { 80.0f, -145.0f };
			wayPoints[2] = { 80.0f, 145.0f };
			wayPoints[3] = { 20, 195.0f };
			wayPoints[4] = { 0.0f, 235.0f };
			break;
		case 1:
			wayPoints[0] = { 0.0f, -195.0f };
			wayPoints[1] = { 0.0f, -140.0f };
			wayPoints[2] = { 0.0f, 0.0f };
			wayPoints[3] = { 0.0f, 140.0f };
			wayPoints[4] = { 0.0f, 235.0f };
			break;
		case 2:
			wayPoints[0] = { -20.0f, -195.0f };
			wayPoints[1] = { -80.0f, -145.0f };
			wayPoints[2] = { -80.0f, 145.0f };
			wayPoints[3] = { -20.0f, 195.0f };
			wayPoints[4] = { 0.0f, 235.0f };
			break;
		}
	}
}
