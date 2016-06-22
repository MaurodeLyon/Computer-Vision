#include "stdafx.h"
#include "LeapController.h"

using namespace std;

extern std::vector<Entity*> entities;

void LeapController::onConnect(const Controller& controller)
{
	std::cout << "Leap connected" << std::endl;
}

void LeapController::onFrame(const Controller& controller)
{
	auto frame = controller.frame();
}

LeapController::LeapController()
{
	std::cout << "Leap initialization" << std::endl;
	controller.addListener(*this);
}