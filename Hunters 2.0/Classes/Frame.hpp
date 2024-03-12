#pragma once
#include <SFML/Network.hpp>

using namespace std;

class Frame
{
private:
	sf::IpAddress address;
	sf::Packet receivedPacket;

public:
	Frame();
	Frame(sf::IpAddress,sf::Packet);
	~Frame();
	sf::IpAddress GetAddress();
	sf::Packet GetPacket();
};