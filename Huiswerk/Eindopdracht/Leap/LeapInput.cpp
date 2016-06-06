#include "stdafx.h"
#include "LeapInput.h"

float rightIndexX, rightIndexZ;
float rightThumbX, rightThumbZ;

float leftIndexX, leftIndexZ;
float leftThumbX, leftThumbZ;

void LeapInput::onConnect(const Controller&)
{
	std::cout << "Leap connected" << std::endl;
}

void LeapInput::onFrame(const Controller&)
{
	Frame frame = controller.frame();

	auto rightHand = frame.hands().rightmost();
	for each(auto finger in rightHand.fingers())
	{
		if (finger.type() == Finger::TYPE_INDEX)
		{
			rightIndexX = finger.tipPosition().x;
			rightIndexZ = finger.tipPosition().z;
		}
		if (finger.type() == Finger::TYPE_THUMB)
		{
			rightThumbX = finger.tipPosition().x;
			rightThumbZ = finger.tipPosition().z;
		}
	}
	auto lefthand = frame.hands().leftmost();
	for each(auto finger in lefthand.fingers())
	{
		if (finger.type() == Finger::TYPE_INDEX)
		{
			leftIndexX = finger.tipPosition().x;
			leftIndexZ = finger.tipPosition().z;
		}
		if (finger.type() == Finger::TYPE_THUMB)
		{
			leftThumbX = finger.tipPosition().x;
			leftThumbZ = finger.tipPosition().z;
		}
	}
}
