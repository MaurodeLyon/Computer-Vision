#pragma once
class DisplayManager
{
public:
	static void createDisplay();
	static void updateDisplay();
	static void closeDisplay();
	DisplayManager();
	~DisplayManager();
private:
	const static int WIDTH = 1280;
	const static int HEIGHT = 720;
	const static int FPS_CAP = 120;
};

