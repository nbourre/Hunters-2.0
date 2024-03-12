#include <SFML/Network.hpp>
#include "NetworkManager.hpp"
#include "Frame.hpp"
#include <list>
#include <iostream>

using namespace std;

EventNetwork::EventNetwork()
{
}
EventNetwork::~EventNetwork()
{
	frames.clear();
}

EventNetwork::EventNetwork(unsigned short portSend,unsigned short portReceive)
{
	PortSend = portSend;
	PortReceive = portReceive;
}

void EventNetwork::AddFrame(sf::IpAddress Address, sf::Packet Packet)
{
	Frame myFrame = Frame::Frame(Address,Packet);
	frames.push_back(myFrame);
}

bool EventNetwork::HasEvent()
{
	return (frames.begin() != frames.end());
}

Frame EventNetwork::GetFirstFrame()
{
	Frame returnFrame = *frames.begin();
	frames.pop_front();
	return returnFrame;
}
unsigned short EventNetwork::GetPortReceive()
{
	return (PortReceive);
}

unsigned short EventNetwork::GetPortSend()
{
	return (PortSend);
}