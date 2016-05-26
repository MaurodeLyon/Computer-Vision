#pragma once
class Window
{
public:
	Window();
	~Window();
private:
	static void idle();
	static void passiveMotion(int x, int y);
	static void keyboard(unsigned char key, int, int);
	static void display();
};

