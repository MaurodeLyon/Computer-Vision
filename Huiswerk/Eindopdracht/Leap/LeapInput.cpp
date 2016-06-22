#include "stdafx.h"
#include "LeapInput.h"


Frame frame;

void LeapInput::onConnect(const Controller&)
{
	std::cout << "Leap connected" << std::endl;
}

void LeapInput::onFrame(const Controller&)
{
	Frame frame = controller.frame();
}
