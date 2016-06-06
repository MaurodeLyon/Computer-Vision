// Leap.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	LeapInput * leap = new LeapInput();
	Screen * screen = new Screen();
	return 0;
}

