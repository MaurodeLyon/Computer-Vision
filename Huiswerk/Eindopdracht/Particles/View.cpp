#include "stdafx.h"

unsigned int idleCount, displayCount;


void display()
{
	++displayCount;
}

void idle()
{
	++idleCount;
	glutPostRedisplay();
}

void timer(int time)
{
	std::cout << idleCount << "	" << displayCount << std::endl;
	glutTimerFunc(1000, timer, 1);
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27) exit(0);

}

View::View()
{
	std::cout << "Initializing View" << std::endl;
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "Particles."
	glutCreateWindow("Particles.");
	// Enable Fullscreen
	glutFullScreen();
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutTimerFunc(100, timer, 100);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}


View::~View()
{
}
