#include "stdafx.h"
#include <sstream>


int spellId;
int xcor;
int ycor;
int zcor;

SpellPacket::SpellPacket(int sid, int xpos, int ypos, int zpos)
{
	packetId = 02;
	spellId = sid;
	xcor = xpos;
	ycor = ypos;
	zcor = zpos;
}

void SpellPacket::writeData(Client client) {
	std::string d = "03:" + getData();
	const char*data = d.c_str();
	cout << data << endl;
	client.SendData(data);
}

std::string SpellPacket::getData() {
	std::ostringstream oss;
	oss << spellId << "," << xcor << "," << ycor << "," << zcor;
	return oss.str();
}
