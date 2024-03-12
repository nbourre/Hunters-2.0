#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Cloud : public sf::Sprite
{
private:
	int ID;
	int FlipX; // 1 ou -1
	int FlipY; // 1 ou -1
	int Wind;
	int Angle;
	float Scale;
	float SizeX;
	sf::Texture textureCloud;
public:
	Cloud();
	~Cloud();
	Cloud(int);
	Cloud(int,sf::RenderWindow &win);
	void Draw(sf::RenderWindow &win,float);
};