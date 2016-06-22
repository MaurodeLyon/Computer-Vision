#include "stdafx.h"

void UserInterfaceComponent::render(Entity& entity)
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0, 1000, 1000, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);

	glColor3f(1, 1, 1);
	glutBitmapString("Death count: " + std::to_string(DeathCount), 455, 925);
	
	//glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

void UserInterfaceComponent::glutBitmapString(std::string str, int x, int y)
{
	glRasterPos2f(x, y);
	for (int i = 0; i < str.size(); i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
	}
}