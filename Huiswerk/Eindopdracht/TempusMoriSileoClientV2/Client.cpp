#include "stdafx.h"
#include<Windows.h>
#include<winsock2.h>

#include <mutex>
#pragma comment(lib,"ws2_32.lib") //Winsock Library

#define SERVER "127.0.0.1"  //Ip adres van de server
#define BUFLEN 2048  //Maximale buffer lengte
#define PORT 5902  //Port waarop de server werkt

int slen, s;
struct sockaddr_in si_other;
Client c;
int playerNumber;

extern mutex entitiesLock;

extern std::vector<Entity*> entities;
extern std::vector<Entity*> entitiesToAdd;
extern std::vector<pair<string, ObjModel*>> objectLibrary;

Entity* AddMobs(string rawData) {
	std::string delimiter = ",";

	size_t pos = 0;
	std::vector<std::string> data;
	std::string token;

	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		data.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	data.push_back(rawData);
	auto* mob = new Entity(std::stoi(data.at(0), nullptr, 10), std::stoi(data.at(1), nullptr, 10), std::stoi(data.at(2), nullptr, 10));
	float rot = (std::atof(data.at(3).c_str()))*-1;
	mob->addComponent(new ObjModelComponent(objectLibrary[std::stoi(data.at(4), nullptr, 10)].second, ((rot*180 / PI)+120), 1));
	mob->addComponent(new UnitComponent(200, 1));
	return mob;
}

void DeleteMobs() {
	entitiesLock.lock();
	int size = entities.size();
	for (int i = 0; i < size; i++) {
		Entity * entity = entities.at(i);
		bool del = false;
		for each(Component * c in entity->getComponents()) {
			if (dynamic_cast<const UnitComponent*>(c) != NULL) {
				del = true;
			}
		}
		if (del) {
			size--;
			entities.erase(entities.begin() + i);
		}
	}
	entitiesLock.unlock();
}

void handleMobs(std::string rawData) {
	std::string delimiter = "|";

	size_t pos = 0;
	std::vector<std::string> data;
	std::string token;

	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		data.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	data.push_back(rawData);

	vector<Entity*> mobs;
	for each(std::string mobstring in data) {
		if (mobstring.size() > 0) {
			mobs.push_back(AddMobs(mobstring));
		}
	}

	DeleteMobs();
	for each(Entity* e in mobs) {
		entitiesToAdd.push_back(e);
	}
}


void UpdateCastle(string rawData) {
	std::string delimiter = ",";

	size_t pos = 0;
	std::vector<std::string> data;
	std::string token;

	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		data.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	data.push_back(rawData);
	bool p;
	istringstream(data.at(0)) >> p;


	entitiesLock.lock();
	for each (Entity*e in entities) {
		for each(Component * c in e->getComponents()) {
			if (dynamic_cast<const UnitSpellsFactory*>(c) != NULL) {
				UnitSpellsFactory * usf = (UnitSpellsFactory*)c;
				if (usf->getPlayer()->getPlayer() == p) {
					PlayerComponent * player = usf->getPlayer();
					player->changeHealth(std::stoi(data.at(1), nullptr, 10));
					player->changeEnergy(std::stoi(data.at(2), nullptr, 10));
					player->changeMaxHealth(std::stoi(data.at(3), nullptr, 10));
				}
			}
		}
	}
	entitiesLock.unlock();
}

void handleCastles(std::string rawData) {
	std::string delimiter = "|";

	size_t pos = 0;
	std::vector<std::string> data;
	std::string token;

	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		data.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	data.push_back(rawData);

	for each(std::string castlestring in data) {
		UpdateCastle(castlestring);
	}
}

void DeleteSpells() {
	entitiesLock.lock();
	int size = entities.size();
	for (int i = 0; i < size; i++) {
		Entity * entity = entities.at(i);
		bool del = false;
		for each(Component * c in entity->getComponents()) {
			if (dynamic_cast<const SpellMoveComponent*>(c) != NULL) {
				del = true;
			}
		}
		if (del) {
			size--;
			entities.erase(entities.begin() + i);
		}
	}
	entitiesLock.unlock();
}

Entity* AddSpells(string rawData) {
	std::string delimiter = ",";

	size_t pos = 0;
	std::vector<std::string> data;
	std::string token;

	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		data.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	data.push_back(rawData);
	auto* spell = new Entity(std::stoi(data.at(0), nullptr, 10), std::stoi(data.at(1), nullptr, 10), std::stoi(data.at(2), nullptr, 10));
	spell->addComponent(new ObjModelComponent(objectLibrary[std::stoi(data.at(3), nullptr, 10)].second, 0, 0.5f));
	spell->addComponent(new SpellMoveComponent(0, 0, 0, 1.0f));
	return spell;
}


void handleSpells(std::string rawData) {
	std::string delimiter = "|";

	size_t pos = 0;
	std::vector<std::string> data;
	std::string token;

	while ((pos = rawData.find(delimiter)) != std::string::npos) {
		token = rawData.substr(0, pos);
		data.push_back(token);
		rawData.erase(0, pos + delimiter.length());
	}
	data.push_back(rawData);

	vector<Entity*> spells;
	for each(std::string spellstring in data) {
		if (spellstring.size() > 0) {
			spells.push_back(AddSpells(spellstring));
		}
	}

	DeleteSpells();
	for each(Entity* e in spells) {
		entitiesToAdd.push_back(e);
	}
}

void Client::ParsePacket(char * buf, struct sockaddr_in client) {
	std::string message(buf);
	std::string rawPacketId = message.substr(0, message.find(":"));
	if (message.size() > 2) {
		std::string rawData = message.substr(3);


		switch (atoi(rawPacketId.c_str())) {
		case -1:
			break;
		case 00:
		{

			break;
		}
		case 1:
		{
			handleMobs(rawData);
			break;
		}
		case 2:
		{
			handleCastles(rawData);
			break;
		}
		case 3:
		{
			handleSpells(rawData);
			break;
		}
		case 4:
		{
			std::cout << "STARTING GAME.........PLAYER: " << rawData << endl;
			playerNumber = std::stoi(rawData, nullptr, 10);
			break;
		}
		break;
		}
	}
}


DWORD WINAPI StartConnection(__in LPVOID lpParameter)
{
	s, slen = sizeof(si_other);
	char buf[BUFLEN];
	WSADATA wsa;

	//Initalizeren van winsock2
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
	}


	//Aanmaken van de socket
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR)
	{
		printf("socket() failed with error code : %d", WSAGetLastError());
	}

	//Adres van de server zetten
	memset((char *)&si_other, 0, sizeof(si_other));
	si_other.sin_family = AF_INET;
	si_other.sin_port = htons(PORT);
	si_other.sin_addr.S_un.S_addr = inet_addr(SERVER);

	Sleep(5000);
	while (1)
	{
		memset(buf, '\0', BUFLEN);

		if (recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *) &si_other, &slen) == SOCKET_ERROR)
		{
			//printf("recvfrom() failed with error code : %d", WSAGetLastError());
		}

		bool added = false;
		int i = 0;
		while (added == false) {
			if (buf[i] == 0) {
				buf[i] = '\0';
				added = true;
			}
			i++;
		}
		c.ParsePacket(buf, si_other);
	}

	closesocket(s);
	WSACleanup();
	return 0;
}

void start() {
	DWORD threadID1;
	HANDLE clientThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)StartConnection, 0, 0, &threadID1);
}

Client::Client() {
	playerNumber = 0;
	start();
	cout << "Thread started" << endl;
	c = this;
}

Client::Client(Client*client) {

}

void Client::SendData(const char*data) {

	if (sendto(s, data, strlen(data), 0, (struct sockaddr *) &si_other, slen) == SOCKET_ERROR)
	{
		printf("sendto() failed with error code : %d", WSAGetLastError());
	}
}

