#ifndef PACKET_H
#define PACKET_H

#pragma once
#include "stdafx.h"
class Packet {
	public:
		virtual void writeData(Client client) = 0;
		virtual std::string getData() = 0;
		int packetId;
};
#endif
