#include "stdafx.h"
#include "DisplayManager.h"

Loader loader = Loader();
Renderer renderer = Renderer();
float vertices[] = { -0.5f, 0.5f, 0, -0.5f, -0.5f, 0, 0.5f, -0.5f, 0, 0.5f, -0.5f, 0, 0.5f, 0.5f, 0 - 0.5f, 0.5f, 0 };

void DisplayManager::createDisplay()
{
	std::cout << "Initializing display manager" << std::endl;
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Set the window size
	glutInitWindowSize(WIDTH, HEIGHT);
	// Create the window with the title "Particles."
	glutCreateWindow("Particles.");
	// Enable Fullscreen
	glutFullScreen();
	//display function
	glutDisplayFunc(updateDisplay);
	glutCloseFunc(closeDisplay);
	glutMainLoop();
}

void DisplayManager::updateDisplay()
{
	glutPostRedisplay();
}

void DisplayManager::closeDisplay()
{
	exit(0);
}

DisplayManager::DisplayManager()
{
}


DisplayManager::~DisplayManager()
{
}

