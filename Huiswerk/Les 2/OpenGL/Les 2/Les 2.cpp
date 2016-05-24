// Les 2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

struct Vertex
{
	float x;
	float y;
	float z;
};

std::vector<Vertex> vertices;
void initVertices()
{
	vertices.push_back(Vertex{ -1,-1, 1 });
	vertices.push_back(Vertex{ -1, 1, 1 });
	vertices.push_back(Vertex{  1, 1, 1 });
	vertices.push_back(Vertex{  1,-1, 1 });
	vertices.push_back(Vertex{ -1,-1,-1 });
	vertices.push_back(Vertex{ -1, 1,-1 });
	vertices.push_back(Vertex{  1, 1,-1 });
	vertices.push_back(Vertex{  1,-1,-1 });
}

GLfloat color[8][3] = //rgb
{
	{ 0.0,0.0,0.0 }, //white
	{ 1.0,0.0,0.0 }, //red
	{ 1.0,1.0,0.0 }, //red+green
	{ 0.0,1.0,0.0 }, //green
	{ 0.0,1.0,1.0 }, //green+blue
	{ 0.0,0.0,1.0 }, //blue
	{ 1.0,0.0,1.0 }, //red+blue
	{ 1.0,1.0,1.0 }, //black
};

void draw()
{
		glVertexPointer(3,GL_FLOAT,)
}

void display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	auto w = glutGet(GLUT_WINDOW_WIDTH);
	auto h = glutGet(GLUT_WINDOW_HEIGHT);
	gluPerspective(60, w / h, 0.1, 100);
	glMatrixMode(GL_MODELVIEW);

	//middle cube
	glLoadIdentity();
	gluLookAt(0, -10, -10, 0, 0, 0, 0, 0, 1);
	draw();

	glutSwapBuffers();
}

void idle()
{
	glutPostRedisplay();
}

int main(int argc, char* argv[]) {
	// Initialize GLUT
	glutInit(&argc, argv);
	// Set up some memory buffers for our display
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	// Set the window size
	glutInitWindowSize(1280, 780);
	// Create the window with the title "Les 2"
	glutCreateWindow("Les 2");
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();
	return 0;
}

