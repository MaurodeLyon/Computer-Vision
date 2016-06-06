#pragma once
class Screen
{
public:
	Screen();
	~Screen(){};
private:

	static void idle();
	static void passiveMotion(int x, int y);
	static void keyboard(unsigned char key, int, int);
	static void display();
	static void timer(int);
};

