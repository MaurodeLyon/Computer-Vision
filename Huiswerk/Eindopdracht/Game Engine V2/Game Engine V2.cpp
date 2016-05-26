// Game Engine V2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

using namespace  std;

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	Entity* e = new Entity();
	Window* d = new Window();
	cout << "velocity: " << e->velocity << " x: " << e->x << " y: " << e->y << " z: " << e->z << endl;
	return 0;
}

