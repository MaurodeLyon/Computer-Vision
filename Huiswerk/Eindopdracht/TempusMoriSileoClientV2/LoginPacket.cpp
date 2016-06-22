#include "stdafx.h"

LoginPacket::LoginPacket(char * data) {
	packetId = 00;
	username = std::string(data);
}

LoginPacket::LoginPacket(std::string data) {
	packetId = 00;
	username = std::string(data);
}

void LoginPacket::writeData(Client client) {
	std::string d = "00:"+  getData();
	const char*data = d.c_str();
	client.SendData(data);
}

std::string LoginPacket::getData() {
	return username;
}
