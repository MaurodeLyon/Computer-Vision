#pragma once
#include "stdafx.h"

class MobPacket : public Packet
{
public:
	MobPacket(int x, int y);
	void writeData(Client client);
	std::string getData();
};