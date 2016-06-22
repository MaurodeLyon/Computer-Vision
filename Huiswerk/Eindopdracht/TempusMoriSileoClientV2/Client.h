#pragma once
#ifndef CLIENT_H
#define CLIENT_H
#include<WinSock2.h>

class Client
{
public:
	void ParsePacket(char * buf, struct sockaddr_in client);
	Client();
	Client(Client*client);
	void SendData(const char*data);
};
#endif