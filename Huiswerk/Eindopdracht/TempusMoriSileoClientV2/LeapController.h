#pragma once
using namespace Leap;

class LeapController :public Listener
{
public:
	LeapController();
	~LeapController(){};
	void onConnect(const Controller&) override;
	void onFrame(const Controller&) override;
private:
	Controller controller;
};

