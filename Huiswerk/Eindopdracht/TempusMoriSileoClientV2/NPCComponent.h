#pragma once
class NPCComponent : public Component
{
public:
	struct Point2D { float x; float z; };

	NPCComponent(float speed, float lane, bool player, bool hasCollision, float collisionRadius);
	~NPCComponent() {};

	virtual void update(Entity& entity);

	float getSpeed() { return speed; }
	void setSpeed(float speed) { this->speed = speed; }
	bool hasCollionEnabled;
	void setTarget(Entity * entity);

private:
	int currentWaypoint;
	bool player;
	float speed, direction;
	float collisionRadius;

	Point2D destination;
	Point2D position;
	Point2D target;
	Point2D wayPoints[5];

	void rotations();
	void generateWaypoints(bool player, int lane);
	void newTarget(Entity * entity);
	float baseSpeed;
};

