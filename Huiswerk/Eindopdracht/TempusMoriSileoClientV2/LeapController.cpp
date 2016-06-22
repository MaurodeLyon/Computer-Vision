#include "stdafx.h"
#include "LeapController.h"

using namespace std;

extern std::vector<Entity*> entities;
extern int x;
extern int y;

void LeapController::onConnect(const Controller& controller)
{
	std::cout << "Leap connected" << std::endl;
}

void LeapController::onFrame(const Controller& controller)
{
	auto frame = controller.frame();
	x = frame.hands().rightmost().palmPosition().x;
	y = frame.hands().rightmost().palmPosition().y -200;
}

LeapController::LeapController()
{
	std::cout << "Leap initialization" << std::endl;
	controller.addListener(*this);
}