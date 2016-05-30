#pragma once
class GameEngine
{
public:
	GameEngine();
	~GameEngine();
	void addEntity(Entity*);
	void removeEntity(int ID);
	std::vector<Entity*> entities;
private:

};

