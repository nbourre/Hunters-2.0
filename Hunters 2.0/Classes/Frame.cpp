#include <SFML/Network.hpp>
#include "Frame.hpp"

using namespace std;

Frame::Frame() {}
Frame::Frame(sf::IpAddress Address,sf::Packet Packet)
{
	address    = Address;
	receivedPacket = Packet;
}
Frame::~Frame(){}

sf::IpAddress Frame::GetAddress()
{
	return address;
}

sf::Packet Frame::GetPacket()
{
	return receivedPacket;
}