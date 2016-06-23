// Dodger.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

int main(int argc, char* argv[])
{
	srand(time(NULL));
	glutInit(&argc, argv);
	LeapController * leap = new LeapController();
	Window* window = new Window();
	ObjLibrary* lib = new ObjLibrary();
	lib->loadObjects();
	Engine* engine = new Engine();

	glutMainLoop();
	return 0;
}
