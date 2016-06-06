#pragma once
using namespace Leap;
class LeapInput : public Listener
{
public:
	LeapInput() {
		controller.addListener(*this);
	};
	~LeapInput() {};
	void onConnect(const Controller&);
	void onFrame(const Controller&);
private:
	Controller controller;
};

