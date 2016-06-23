#pragma once
class AstroidComponent : public Component
{
public:
	AstroidComponent(int speed) : speed(speed) {};
	~AstroidComponent() {};

	void update(Entity& entity) override;
private:
	int speed;
};

