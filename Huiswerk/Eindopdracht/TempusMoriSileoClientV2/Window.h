#pragma once
#include "stdafx.h"

class Window
{
public:
	Window();
	~Window(){};
private:
	bool keys[255];

	static void idle();
	static void passiveMotion(int x, int y);
	static void keyboard(unsigned char key, int, int);
	static void display();

};

