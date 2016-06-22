#include "stdafx.h"
#include "AttackComponent.h"

extern Audio audio;
extern vector<Entity*> entities;
extern int ticks;
void AttackComponent::update(Entity &entity)
{
	UnitComponent* ownUnit;
	UnitComponent* otherUnit;
	NPCComponent* ownNpc;

	attackUpdateLocation(entity.x, entity.z);
	hasAggro = false;
	isAttacking = false;

	for each(Component * own_component in entity.getComponents())
		if (dynamic_cast<const UnitComponent*>(own_component) != NULL) {
			ownUnit = (UnitComponent*)own_component;
			for each(Entity* otherEntity in entities) {
				if (&entity != otherEntity) {
					for each(Component * otherComponent in otherEntity->getComponents())
						if (dynamic_cast<const UnitComponent*>(otherComponent) != NULL && attackIntersect(otherEntity->x, otherEntity->z))	//if entity is unit and is in attackRange
						{
							for each(Component * com in entity.getComponents()) {
								if (dynamic_cast<NPCComponent*>(com) != nullptr) {
									ownNpc = (NPCComponent*)com;

									//cout << "Attack intersect: " << attackIntersect(otherEntity->x, otherEntity->z) << endl;
									otherUnit = (UnitComponent*)otherComponent;

									//cout << "Own unit player: " << ownUnit->getPlayer() << "\tOther unit player: " << otherUnit->getPlayer() << endl;
									if (ownUnit->getPlayer() != otherUnit->getPlayer()) {
										//update target to enemy else dmg health and stop collision
										if (distance > attRange) {
											hasAggro = true;
											ownNpc->hasCollionEnabled = true;
											ownNpc->setTarget(otherEntity);
										}
										// Stop collision and dmg mob
										else {
											ownNpc->hasCollionEnabled = false;
											hasAggro = true;
											isAttacking = true;
											if (ticks % 30 == 0) {
												otherUnit->removeHP(damage);
												cout << "remove hp" << endl;
											}
										}
									}
								}
							}
						}
				}
			}
		}
}

bool AttackComponent::attackIntersect(float box2_x, float box2_z)
{
	auto distanceToTarget = attackDistance(box2_x, box2_z);
	distance = distanceToTarget;
	if (distanceToTarget <= attackRadius) return true;
	return false;
}

float AttackComponent::attackDistance(float x, float z)
{
	auto distance = sqrtf(powf(fabsf(attackBoxLocation.x - x), 2) + powf(fabsf(attackBoxLocation.z - z), 2));
	return distance;
}

void AttackComponent::attackUpdateLocation(int x, int z)
{
	attackBoxLocation.x = x + 5;
	attackBoxLocation.z = z - 5;
}
