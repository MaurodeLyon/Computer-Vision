// Game Engine.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);	// Initialize GLUT
	DisplayManager display;
	display.createDisplay();


	return 0;
}

