#define STB_IMAGE_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>
#include <GL/freeglut.h>
#include <math.h>

#include "stb_image.h"
#include <math.h>
#include <algorithm>
#include <iostream>
#include <vector>


struct Camera
{
	float posX = 0;
	float posY = -4;
	float posZ = 0;
	float rotX = 0;
	float rotY = 0;
	float speedY = 0;
} camera;
bool keys[255];
float lastFrameTime = 0;
int width, height;
unsigned int grass_texture_id;
unsigned int atlas_texture_id;
typedef std::vector<std::vector<std::vector<int> > > world;

void drawCube(int value)
{
	auto i = value;
	i = i % 256;
	auto x1 = float((i % 16) * 0.0625);
	auto y1 = float((i * 0.0625) * 0.0625);
	auto x2 = float(x1 + 0.0625);
	auto y2 = float(y1 + 0.0625);
	//printf("i: %d\tx1: %f\tx2: %f\ty1: %f\ty2: %f\n",i, x1, x2, y1, y2);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, atlas_texture_id);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	//
	glTexCoord2f(x1, y1); glVertex3f(-1, -1, -1);
	glTexCoord2f(x2, y1); glVertex3f(1, -1, -1);
	glTexCoord2f(x2, y2); glVertex3f(1, 1, -1);
	glTexCoord2f(x1, y2); glVertex3f(-1, 1, -1);

	glColor3f(1, 1, 1);
	glTexCoord2f(x1, y1); glVertex3f(-1, -1, 1);
	glTexCoord2f(x2, y1); glVertex3f(1, -1, 1);
	glTexCoord2f(x2, y2); glVertex3f(1, 1, 1);
	glTexCoord2f(x1, y2); glVertex3f(-1, 1, 1);

	//glColor3f(0, 0, 1);
	glTexCoord2f(x1, y1); glVertex3f(-1, -1, -1);
	glTexCoord2f(x2, y1); glVertex3f(-1, 1, -1);
	glTexCoord2f(x2, y2); glVertex3f(-1, 1, 1);
	glTexCoord2f(x1, y2); glVertex3f(-1, -1, 1);

	//glColor3f(1, -1, 1);
	glTexCoord2f(x1, y1); glVertex3f(1, -1, -1);
	glTexCoord2f(x2, y1); glVertex3f(1, 1, -1);
	glTexCoord2f(x2, y2); glVertex3f(1, 1, 1);
	glTexCoord2f(x1, y2); glVertex3f(1, -1, 1);

	//glColor3f(0, 1, 0);
	glTexCoord2f(x1, y1); glVertex3f(-1, -1, -1);
	glTexCoord2f(x2, y1); glVertex3f(1, -1, -1);
	glTexCoord2f(x2, y2); glVertex3f(1, -1, 1);
	glTexCoord2f(x1, y2); glVertex3f(-1, -1, 1);

	//glColor3f(1, 1, 0);
	glTexCoord2f(x1, y1); glVertex3f(-1, 1, -1);
	glTexCoord2f(x2, y1); glVertex3f(1, 1, -1);
	glTexCoord2f(x2, y2); glVertex3f(1, 1, 1);
	glTexCoord2f(x1, y2); glVertex3f(-1, 1, 1);
	glEnd();
	glDisable(GL_TEXTURE_2D);
}

void display()
{
	glClearColor(0.0f, 0.5f, 1.0f, 1);
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.0f, (float)width / height, 0.1, 30);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glRotatef(camera.rotX, 1, 0, 0);
	glRotatef(camera.rotY, 0, 1, 0);
	glTranslatef(camera.posX, camera.posY, camera.posZ);

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, grass_texture_id);
	glBegin(GL_QUADS);
	glColor3f(1, 1, 1);
	glTexCoord2f(0, 0); glVertex3f(-15, -1, -15);
	glTexCoord2f(1, 0); glVertex3f(15, -1, -15);
	glTexCoord2f(1, 1); glVertex3f(15, -1, 15);
	glTexCoord2f(0, 1); glVertex3f(-15, -1, 15);
	glEnd();
	glDisable(GL_TEXTURE_2D);
	for (auto x = -10; x <= 10; x += 2)
	{
		for (auto y = -10; y <= 10; y += 2)
		{
			for (auto z = -10; z <= 10; z += 2)
			{
				glPushMatrix();
				glTranslatef(float(x), float(z), float(y));
				drawCube(16);
				glPopMatrix();
			}
		}
	}

	glutSwapBuffers();
}

void move(float angle, float fac)
{
	camera.posX += (float)cos((camera.rotY + angle) / 180 * M_PI) * fac;
	camera.posZ += (float)sin((camera.rotY + angle) / 180 * M_PI) * fac;
}

void idle()
{
	float frameTime = glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
	float deltaTime = frameTime - lastFrameTime;
	lastFrameTime = frameTime;

	const float speed = 5;
	if (keys['a']) move(0, deltaTime*speed);
	if (keys['d']) move(180, deltaTime*speed);
	if (keys['w']) move(90, deltaTime*speed);
	if (keys['s']) move(270, deltaTime*speed);
	if (camera.posY == -4) if (keys[' '])  camera.speedY = 4;

	camera.posY -= camera.speedY * deltaTime;		//jump
	if (camera.posY > -4)							//ground collision
		camera.posY = -4;
	camera.speedY -= float(9.81 * deltaTime);				//gravity

	glutPostRedisplay();
}

void mousePassiveMotion(int x, int y)
{
	int dx = x - width / 2;
	int dy = y - height / 2;
	if ((dx != 0 || dy != 0) && abs(dx) < 400 && abs(dy) < 400)
	{
		camera.rotY += dx / 10.0f;
		camera.rotX += dy / 10.0f;
		glutWarpPointer(width / 2, height / 2);
	}
}

void keyboard(unsigned char key, int, int)
{
	if (key == 27)
		exit(0);
	keys[key] = true;
}

void keyboardUp(unsigned char key, int, int)
{
	keys[key] = false;
}

int main(int argc, char* argv[])
{
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1024, 768);
	glutInit(&argc, argv);
	glutCreateWindow("Maurocraft");

	memset(keys, 0, sizeof(keys));
	glEnable(GL_DEPTH_TEST);

	int img_width, img_height, bpp;
	unsigned char* imgData = stbi_load("grass_grass_0099_02_preview.jpg", &img_width, &img_height, &bpp, 4);
	glGenTextures(1, &grass_texture_id);
	glBindTexture(GL_TEXTURE_2D, grass_texture_id);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,					//level
		GL_RGBA,			//internal format
		img_width,			//width
		img_height,			//height
		0,					//border
		GL_RGBA,			//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);			//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(imgData);

	imgData = stbi_load("terrain.png", &img_width, &img_height, &bpp, 4);
	glGenTextures(1, &atlas_texture_id);
	glBindTexture(GL_TEXTURE_2D, atlas_texture_id);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,					//level
		GL_RGBA,			//internal format
		img_width,			//width
		img_height,			//height
		0,					//border
		GL_RGBA,			//data format
		GL_UNSIGNED_BYTE,	//data type
		imgData);			//data
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	stbi_image_free(imgData);

	glutIdleFunc(idle);
	glutDisplayFunc(display);
	glutReshapeFunc([](int w, int h) { width = w; height = h; glViewport(0, 0, w, h); });
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutPassiveMotionFunc(mousePassiveMotion);

	glutWarpPointer(width / 2, height / 2);
	glutSetCursor(GLUT_CURSOR_NONE);

	glutMainLoop();


	return 0;
}