#pragma once
#include "stdafx.h"

class LoginPacket : public Packet
{
public:
	LoginPacket(char* data);
	LoginPacket(std::string data);
	void writeData(Client client);
	std::string getData();

private:
	std::string username;
};