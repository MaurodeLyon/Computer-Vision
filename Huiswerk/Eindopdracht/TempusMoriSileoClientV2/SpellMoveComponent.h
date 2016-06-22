#pragma once
struct Position
{
	float x;
	float y;
	float z;
	Position()
	{
		x = y = z = 0;
	}

	Position(float x, float y, float z) : x(x), y(y), z(z) {}
};

class SpellMoveComponent : public Component
{
public:
	SpellMoveComponent(float targetX, float targetY, float targetZ, float speed);
	~SpellMoveComponent();

	void update(Entity& entity) override;
	void move(Entity& entity);

private:
	Position targetPos;
	Position distance;
	float speed;
};

