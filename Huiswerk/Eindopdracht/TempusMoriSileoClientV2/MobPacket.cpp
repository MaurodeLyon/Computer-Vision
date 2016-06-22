#include "stdafx.h"
#include <sstream>


int unitId;
int lane;

MobPacket::MobPacket(int uid, int l)
{
	packetId = 01;
	unitId = uid;
	lane = l;
}

void MobPacket::writeData(Client client) {
	std::string d = "01:" + getData();
	const char*data = d.c_str();
	cout << data << endl;
	client.SendData(data);
}

std::string MobPacket::getData() {
	std::ostringstream oss;
	oss << unitId << "," << lane;
	return oss.str();
}
