// Game Engine V2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace  std;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	Entity* a = new Entity();
	Entity* b = new Entity();
	Entity* c = new Entity();
	Entity* d = new Entity();
	Entity* e = new Entity();

	GameEngine* g = new GameEngine();
	g->addEntity(a);
	g->addEntity(b);
	g->addEntity(c);
	g->addEntity(d);
	g->addEntity(e);
	for each (Entity* p in g->entities)
	{
		cout << "ID: " << p->ID << endl;
	}
	cout << "size: " << g->entities.size() << endl;

	g->removeEntity(3);

	for each (Entity* p in g->entities)
	{
		cout << "ID: " << p->ID << endl;
	}
	cout << "size: " << g->entities.size() << endl;
	//cout << "velocity: " << e->velocity << " x: " << e->x << " y: " << e->y << " z: " << e->z << endl;

	Window* w = new Window();
	return 0;
}

