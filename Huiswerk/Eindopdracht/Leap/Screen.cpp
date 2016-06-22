#include "stdafx.h"
#include "Screen.h"


int lastFrameTime;
extern Frame frame;

Screen::Screen()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 800);
	glutCreateWindow("Eindopdracht OpenGL");
	//glutFullScreen();

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	//glEnable(GL_LIGHTING);
	//glEnable(GL_LIGHT0);
	//glEnable(GL_LIGHT1);
	//glEnable(GL_LIGHT2);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passiveMotion);
	glutTimerFunc(50, timer, 0);

	glutMainLoop();
}

void Screen::display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	gluPerspective(90, 1, 0.1f, 10000);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	gluLookAt(0, 100, 100,
		0, 0, 0,
		0, 1, 0);

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X axis is red.
	glVertex3f(0, 0, 0);
	glVertex3f(10000, 0, 0);
	glColor3f(0, 1, 0); // Y axis is green.
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10000, 0);
	glColor3f(0, 0, 1); // rightIndexZ axis is blue.
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 10000);
	glEnd();
	glPopMatrix();

	



	glutSwapBuffers();
}

void Screen::idle()
{
	glutPostRedisplay();
}

void Screen::timer(int value)
{
	auto frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	auto deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;
	glutTimerFunc(50, timer, 0);
}

void Screen::keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
}

void Screen::passiveMotion(int x, int y)
{
}