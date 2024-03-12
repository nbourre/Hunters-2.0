#pragma once
#include <SFML/Network.hpp>
#include "Frame.hpp"
#include <list>
#include <iostream>

using namespace std;

class EventNetwork
{
private:
	list<Frame> frames;
	unsigned short PortSend;
	unsigned short PortReceive;
public:
	EventNetwork();
	~EventNetwork();
	EventNetwork(unsigned short,unsigned short);
	void AddFrame(sf::IpAddress, sf::Packet);
	bool HasEvent();
	Frame GetFirstFrame();
	unsigned short GetPortReceive();
	unsigned short GetPortSend();
};