#pragma once
struct TrainPosition
{
	float x;
	float y;
	float z;
	TrainPosition()
	{
		x = y = z = 0;
	}

	TrainPosition(float x, float y, float z) : x(x), y(y), z(z) {}
};
class TrainMoveComponent : public Component
{
public:
	TrainMoveComponent(float targetX, float targetY, float targetZ, float speed);
	~TrainMoveComponent();
	void update(Entity& entity) override;
	void move(Entity& entity);

private:
	Position targetPos;
	Position distance;
	float speed;
};

