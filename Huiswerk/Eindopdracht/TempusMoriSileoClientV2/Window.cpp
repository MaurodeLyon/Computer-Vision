#include "stdafx.h"
#include "Window.h"


extern std::vector<pair<string, ObjModel*>> objectLibrary;
extern std::vector<Entity*> entities;
extern std::vector<Entity*> entitiesToAdd;

extern int playerNumber;
mutex entitiesLock;

//QUICK FIX VARIABLES TO BE REMOVED
int mousePosX, mousePosY;
int width, height;
bool inMenu = true;
bool inGame = false;
bool toggle = true;
float rot = 0;

void update(int value)
{
	//update entities
	entitiesLock.lock();
	if (entitiesToAdd.size() > 0)
	{
		//add entities to game
		for each(Entity* e in entitiesToAdd)
		{
			entities.push_back(e);
		}
		//remove entities from hold position
		entitiesToAdd.clear();
	}

	for each(Entity * e in entities) {
		e->update();
	}
	entitiesLock.unlock();
}


Window::Window()
{
	memset(keys, 0, sizeof(keys));
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1280, 800);
	glutCreateWindow("Dodger");
	//glutFullScreen();

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

	//glutTimerFunc(50, update, 0);
	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutKeyboardFunc(keyboard);
	glutPassiveMotionFunc(passiveMotion);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutWarpPointer(width / 2, height / 2);
}

int fps = 60;
float timePerTick = 1000 / fps;
float delta = 0;
long oldTimeSinceStart = 0;
long timeSinceStart = 0;
float timer = 0;
int ticks = 0;
void Window::idle()
{
	timeSinceStart = glutGet(GLUT_ELAPSED_TIME);
	delta += (timeSinceStart - oldTimeSinceStart) / timePerTick;
	timer += timeSinceStart - oldTimeSinceStart;
	oldTimeSinceStart = timeSinceStart;
	//std::cout << timer << std::endl;
	if (delta >= 1)
	{
		update(0);
		glutPostRedisplay();
		ticks++;
		delta--;
	}

	if (timer >= 1000)
	{
		//std::cout << "Frames per second::";
		//std::cout << ticks << std::endl;
		timer = 0;
		ticks = 0;
	}

}
void Window::passiveMotion(int x, int y)
{
	int dx = x - width / 2;
	int dy = y - height / 2;
	mousePosX = x;
	mousePosY = y;
	//std::cout << "x:" << x << std::endl;
	//std::cout << "y:" << y << std::endl;
}

int keyPressed;
int x;
int y;
void Window::keyboard(unsigned char key, int, int)
{
	keyPressed = key;
	if (key == 'w') y += 5;
	if (key == 'a') x -= 5;
	if (key == 's') y -= 5;
	if (key == 'd') x += 5;
	if (key == 27) exit(0);
}

void Window::display()
{
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	width = glutGet(GLUT_WINDOW_WIDTH);
	height = glutGet(GLUT_WINDOW_HEIGHT);

	gluPerspective(90, 1, 0.1f, 15000);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(0, 150, 250, 0, 0, 0, 0, 1, 0);
	//gluLookAt(leapx, leapy, leapz - 100, 0, 0, 0, 0, 1, 0);

	//render entities
	glColor3f(1, 1, 1);

	entitiesLock.lock();
	for (vector<Entity*>::iterator it = entities.begin(); it != entities.end();)
	{
		Entity* e = *it;
		if (e->alive)
		{
			glPushMatrix();
			e->render();
			glPopMatrix();
			++it;
		}
	}
	entitiesLock.unlock();


	glPushMatrix();
	glBegin(GL_LINES);
	glColor3f(1, 0, 0); // X axis is red.
	glVertex3f(0, 0, 0);
	glVertex3f(10000, 0, 0);
	glColor3f(0, 1, 0); // Y axis is green.
	glVertex3f(0, 0, 0);
	glVertex3f(0, 10000, 0);
	glColor3f(0, 0, 1); // z axis is blue.
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, 10000);
	glEnd();
	glPopMatrix();

	glutSwapBuffers();
}