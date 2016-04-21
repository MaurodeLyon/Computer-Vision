//Jeff Chastine
#include <Windows.h>
#include <GL\freeglut.h>
#include <iostream>

using namespace std;

double rotate_y = 0;
double rotate_x = 0;

float ver[8][3] =
{
	{ -1.0,-1.0,1.0 },
	{ -1.0,1.0,1.0 },
	{ 1.0,1.0,1.0 },
	{ 1.0,-1.0,1.0 },
	{ -1.0,-1.0,-1.0 },
	{ -1.0,1.0,-1.0 },
	{ 1.0,1.0,-1.0 },
	{ 1.0,-1.0,-1.0 },
};

GLfloat color[8][3] =
{
	{ 0.0,0.0,0.0 },
	{ 1.0,0.0,0.0 },
	{ 1.0,1.0,0.0 },
	{ 0.0,1.0,0.0 },
	{ 0.0,0.0,1.0 },
	{ 1.0,0.0,1.0 },
	{ 1.0,1.0,1.0 },
	{ 0.0,1.0,1.0 },
};

void quad(int a, int b, int c, int d)
{
	glBegin(GL_QUADS);
	glColor3fv(color[a]);
	glVertex3fv(ver[a]);

	glColor3fv(color[b]);
	glVertex3fv(ver[b]);

	glColor3fv(color[c]);
	glVertex3fv(ver[c]);

	glColor3fv(color[d]);
	glVertex3fv(ver[d]);
	glEnd();
}

void colorcube()
{
	quad(0, 3, 2, 1);
	quad(2, 3, 7, 6);
	quad(0, 4, 7, 3);
	quad(1, 2, 6, 5);
	quad(4, 5, 6, 7);
	quad(0, 1, 5, 4);
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60, w / h, 0.1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt
		(
			3, 3, 3,
			0, 0, 0,
			0, 0, 1
			);

	glRotatef(rotate_x, 1.0, 0.0, 0.0);
	glRotatef(rotate_y, 0.0, 1.0, 0.0);
	colorcube();

	glutSwapBuffers();
}

void onIdle()
{
	glutPostRedisplay();
}
void onKeyboard(unsigned char key, int x, int y)
{
	if (key == 27)
	{
		exit(0);
	}
	if (key == 119)
	{
		rotate_y += 5;
	}
	if (key == 115)
	{
		rotate_y -= 5;
	}if (key == 100)
	{
		rotate_x += 5;
	}if (key == 97)
	{
		rotate_x -= 5;
	}
}

void timer(int value)
{
	glutTimerFunc(1000, timer, 1000);
}

int main(int argc, char* argv[]) {
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Set the window size
	glutInitWindowSize(800, 600);
	// Create the window with the title "Hello,GL"
	glutCreateWindow("Hello, world.");
	// Bind the two functions (above) to respond when necessary
	glutKeyboardFunc(onKeyboard);
	glutDisplayFunc(display);
	glutIdleFunc(onIdle);
	glutTimerFunc(1000, timer, 1000);
	glutMainLoop();
	return 0;
}