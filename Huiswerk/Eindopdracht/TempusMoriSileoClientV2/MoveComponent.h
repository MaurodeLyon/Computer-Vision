#pragma once
class MoveComponent : public Component
{
public:
	MoveComponent(float speed, int lane, int player,bool hasCollision);
	~MoveComponent() {};
	virtual void update(Entity& entity);
	virtual void render(Entity& entity) {};

	struct Point2D { float x; float z; }location;

	void onCollision(Entity&);

	float speed;
	float threshold;
	float rotateThreshold;
	float rotation;
	float angle;
	bool autoSpan;
	bool hasCollision;
	int waypointNum;
	int player;
	
	Point2D * wayPoints = new Point2D[5];
	Point2D oldLocation;
	Point2D currentWaypoint;
	Point2D target;
	void generateWaypoints(bool player, int lane);
};

