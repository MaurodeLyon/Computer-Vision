#include "stdafx.h"
#include "MoveComponent.h"
#define	_USE_MATH_DEFINES
#include <math.h>

extern std::vector<Entity*> entities;
//AttackComponent* attComp;
//UnitComponent* ownUnit;
//PlayerComponent* enemyCastle;

MoveComponent::MoveComponent(float speed, int lane, int player, bool hasCollision)
{
	this->player = player + 1;
	generateWaypoints(player, lane);
	location.x = 0.0f;
	this->speed = speed;
	threshold = 1.05f;
	rotateThreshold = 1.0f;
	rotation = 0.0f;
	angle = 0.0f;
	waypointNum = 0;
	oldLocation = location;
	this->hasCollision = hasCollision;
	target = currentWaypoint;
	currentWaypoint = wayPoints[waypointNum];
}

void MoveComponent::update(Entity & entity)
{
	///*Dmg castle on last waypoint*/
	//if (waypointNum >= 4) {
	//	for each(Entity* enemy in entities) {
	//		for each(Component* castleComponent in enemy->getComponents()) {
	//			if (dynamic_cast<const PlayerComponent*>(castleComponent) != NULL) {
	//				//Get enemy castle
	//				enemyCastle = (PlayerComponent*)castleComponent;
	//				//Get own unit component
	//				for each(Component* ownComponent in entity.getComponents()) {
	//					if (dynamic_cast<UnitComponent*>(ownComponent) != NULL) {
	//						ownUnit = (UnitComponent*)ownComponent;
	//					}
	//				}
	//				//TODO check after unitcomponent update to boolean
	//				if (enemyCastle->getPlayer() != ownUnit->getPlayer()) {
	//					//get damage from own attackComponent
	//					for each (Component* deeps in entity.getComponents()) {
	//						if (dynamic_cast<const AttackComponent*>(deeps) != NULL) {
	//							attComp = (AttackComponent*)deeps;
	//						}
	//					}
	//					enemyCastle->lowerHealth(attComp->damage);
	//					entity.alive = false;
	//				}
	//			}
	//		}
	//	}
	//}
	///*Dmg castle on lasy waypoint*/

	oldLocation.x = entity.x;
	oldLocation.z = entity.z;
	Point2D differenceWP = { fabsf(currentWaypoint.x - location.x), fabsf(currentWaypoint.z - location.z) };

	/*Check if x and y are within thesholds, if true update to next waypoint*/
	if (differenceWP.x <= threshold  && differenceWP.z <= threshold) {
		if (waypointNum < 4)												//if not at the end of waypoints
			waypointNum++;													//go to the next waypoint
		currentWaypoint = wayPoints[waypointNum];							//set current waypoint
		target = currentWaypoint;											//target is currentwaypoint
	}

	//Calculate disired rotation towards target;
	rotation = ((atan2f(differenceWP.z, differenceWP.x) * (180 / M_PI)));
	rotation = 90.0f - rotation;

	//transform negatives into positives to determine absolute rotate difference
	auto rotation2 = 0.0f;
	auto angle2 = 0.0f;
	if (rotation < 0)
		rotation2 = rotation * -1;
	else
		rotation2 = rotation;
	if (angle < 0)
		angle2 = angle * -1;
	else
		angle2 = angle;

	auto diffRotate = 0.0f;
	diffRotate = fabsf(angle2 - rotation2);

	//change desired rotation to negative when target is at right side
	if (target.x > location.x) rotation = rotation * -1;

	/*Increase angle if difference is to great*/
	if (diffRotate >= rotateThreshold) {
		if (rotation > angle) 	angle += 2.0f;
		else if (rotation < angle) 	angle -= 2.0f;
	}

	/*Move x if x difference is to great*/
	if (differenceWP.x >= threshold) {
		if (location.x > currentWaypoint.x) location.x -= speed;
		else location.x += speed;
	}

	/*Move y if y difference is to great*/
	if (differenceWP.z >= threshold) {
		if (location.z > currentWaypoint.z) location.z -= speed;
		else location.z += speed;
	}

	entity.x = location.x;
	entity.z = location.z;
}

void MoveComponent::onCollision(Entity & entity)
{
	if (hasCollision) {
		entity.x = oldLocation.x;
		entity.z = oldLocation.z;
		location.z = entity.z;
		location.x = entity.x;
	}
}

void MoveComponent::generateWaypoints(bool player, int lane)
{
	cout << "lane: " << lane << endl;
	//Player 1
	if (player) {
		location.z = 235.0f;
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
		location.z = -235.0f;
		cout << "p2" << endl;
		switch (lane)
		{
		case 0:
			lane = 2;
			break;
		case 1:
			lane = 1;
			break;
		case 2:
			lane = 0;
			break;
		}
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
