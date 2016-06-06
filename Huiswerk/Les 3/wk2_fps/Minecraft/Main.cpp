#define STB_IMAGE_IMPLEMENTATION
#define STB_PERLIN_IMPLEMENTATION
#define _USE_MATH_DEFINES

#include <cstdio>
#include <cmath>
#include <GL/freeglut.h>
#include <math.h>

#include "stb_image.h"
#include "stb_perlin.h"
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

const int WIDTH = 100;
const int HEIGHT = 32;
const int DEPTH = 100;

int *** world = new int**[WIDTH];
bool keys[255];
float lastFrameTime = 0;
int width, height;
unsigned int grass_texture_id;
unsigned int atlas_texture_id;

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

	//glColor3f(1, 1, 1);
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
	gluPerspective(90.0f, (float)width / height, 0.1, 300);

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
	for (auto x = 0; x < 100; x += 1)
	{
		for (auto y = 0; y < 32; y += 1)
		{
			for (auto z = 0; z < 100; z++)
			{
				glPushMatrix();
				glTranslatef(float(x + x), float(y + y + stb_perlin_noise3(x, y, z, 0, 0, 0)), float(z + z));
				if (world[x][y][z] == -1);
				else if (world[x][y][z] == 1)
				{
					drawCube(0);
				}
				else if (world[x][y][z] == 2)
				{
					drawCube(17);
				}

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
	//if (camera.posY == -4)
	if (keys[' '])  camera.posY -= 1;
	if (keys['x'])  camera.posY += 1;

	/*camera.posY -= camera.speedY * deltaTime;		//jump
	if (camera.posY > -4)							//ground collision
		camera.posY = -4;
	camera.speedY -= float(9.81 * deltaTime);				//gravity
	*/
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


	for (int x = 0; x < WIDTH; x++)
	{
		world[x] = new int*[HEIGHT];
		for (int y = 0; y < HEIGHT; y++)
		{
			world[x][y] = new int[DEPTH];
			for (int z = 0; z < DEPTH; z++)
			{
				if (y == 16)
					world[x][y][z] = 1;
				else if (y < 16)
					world[x][y][z] = 2;
				else
					world[x][y][z] = -1;
			}
		}
	}

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