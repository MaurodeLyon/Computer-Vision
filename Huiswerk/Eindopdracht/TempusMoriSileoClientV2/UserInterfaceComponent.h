#pragma once
using namespace std;
class UserInterfaceComponent : public Component
{
public:
	int DeathCount;

	UserInterfaceComponent() : DeathCount(0) {};
	~UserInterfaceComponent() {};

	virtual void render(Entity& entity);

	void glutBitmapString(std::string str, int x, int y);
};

