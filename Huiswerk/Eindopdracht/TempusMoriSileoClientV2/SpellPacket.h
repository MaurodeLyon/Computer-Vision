#pragma once
#include "stdafx.h"

class SpellPacket : public Packet
{
public:
	SpellPacket(int spellId,int x, int y, int z);
	void writeData(Client client);
	std::string getData();
};