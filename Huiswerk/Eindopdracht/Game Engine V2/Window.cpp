#include "stdafx.h"
#include "Window.h"

bool keys[255];
int width, height;
float lastFrameTime = 0;

Window::Window()
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 800);
	glutCreateWindow("Eindopdracht OpenGL");
	//glutFullScreen();

	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHT1);
	glEnable(GL_LIGHT2);
	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.01f);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passiveMotion);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });

	glutWarpPointer(width / 2, height / 2);
	glutMainLoop();
}


Window::~Window()
{
}


void Window::idle()
{
	auto frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	auto deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;
	glutPostRedisplay();
}
int xx, yy;
void Window::passiveMotion(int x, int y)
{
	xx = x;
	yy = y;
	int dx = x - width / 2;
	int dy = y - height / 2;
	std::cout << "x:" << x << std::endl;
	std::cout << "y:" << y << std::endl;
	/*if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
	camera.rotY += dx / 10.0f;
	camera.rotX += dy / 10.0f;
	glutWarpPointer(width / 2, height / 2);
	}
	*/
}
bool toggle = true;
void Window::keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	if (key == ' ')
		toggle = !toggle;
	keys[key] = true;
}

void Window::display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	if (toggle) glOrtho(-width, width, height, -height, 0.1f, 10000);
	else gluPerspective(90, 1, 0.1f, 10000);


	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(width / 2, height / 2, 1000,
			  width / 2, height / 2, 0,
			  0, 1, 0);

	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X axis is red.
	glVertex3f(width / 2, height / 2, 0);
	glVertex3f(10000, height / 2, 0);
	glColor3f(0, 1, 0); // Y axis is green.
	glVertex3f(width / 2, height / 2, 0);
	glVertex3f(width / 2, 10000, 0);
	glColor3f(0, 0, 1); // z axis is blue.
	glVertex3f(width / 2, height / 2, 0);
	glVertex3f(width / 2, height / 2, 10000);
	glEnd();
	glPopMatrix();

	/*	GLfloat LightAmbient[] = { 255 / 255.0f, 147 / 255.0f, 41 / 255.0f, 0.1f };
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, LightAmbient);
	glLightfv(GL_LIGHT2, GL_SPECULAR, LightAmbient);

	glFogi(GL_FOG_MODE, GL_LINEAR);        // Fog Mode
	GLfloat fogColor[4] = { 0.6f, 0.6f, 1,1.0f };
	glFogfv(GL_FOG_COLOR, fogColor);            // Set Fog Color
	glFogf(GL_FOG_DENSITY, 0.05f);              // How Dense Will The Fog Be
	glHint(GL_FOG_HINT, GL_DONT_CARE);          // Fog Hint Value
	glFogf(GL_FOG_START, 30.0f);             // Fog Start Depth
	glFogf(GL_FOG_END, 85.0f);               // Fog End Depth
	//glEnable(GL_FOG);                   // Enables GL_FOG


	////glPushMatrix();   // MARTIJN
	////glBegin(GL_QUADS);
	////glColor3f(1, 0, 1);
	////int blockSIZE = 0;
	////glVertex3f(blockSIZE, blockSIZE, 1);
	////glVertex3f(1, blockSIZE, 1);
	////glVertex3f(1, 1, 1);
	////glVertex3f(blockSIZE, 1, 1);
	////glEnd();
	////glPopMatrix();
	//
	//glEnd();*/
	std::string text = "";
	if(toggle) text = "Ortho";
	else text = "Perspective";
	
	glRasterPos3f(500, 500, 0);
	for (auto &character : text) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, character);

	glutSwapBuffers();
}