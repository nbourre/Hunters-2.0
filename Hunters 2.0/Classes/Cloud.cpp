#include <SFML/Graphics.hpp>
#include "Cloud.hpp"

using namespace std;

Cloud::Cloud()
{
}
Cloud::Cloud(int Id)
{
	ID = Id;
	if((rand() % 2 == 0)) FlipX = -1; else FlipX = 1;
	if((rand() % 2 == 0)) FlipY = -1; else FlipY = 1;
	Scale = (float)((rand() % 6) + 2);
	Wind = rand() % 4 + 5;
	Angle = rand() % 360;
	switch (rand() % 3)
	{
	case 0:
		textureCloud.loadFromFile("Images/Cloud0.png");
		break;
	case 1:
		textureCloud.loadFromFile("Images/Cloud1.png");
		break;
	case 2:
		textureCloud.loadFromFile("Images/Cloud2.png");
		break;
	}
	SizeX = textureCloud.getSize().x / Scale;
	setOrigin(0,0);
	setPosition(3000.0f,(float)((rand() % 400) - 20));
}

Cloud::Cloud(int Id,sf::RenderWindow &win)
{
	ID = Id;
	if((rand() % 2 == 0)) FlipX = -1; else FlipX = 1;
	if((rand() % 2 == 0)) FlipY = -1; else FlipY = 1;
	Scale = (float)((rand() % 6) + 2);
	Wind = rand() % 4 + 5;
	Angle = rand() % 360;
	switch (rand() % 3)
	{
	case 0:
		textureCloud.loadFromFile("Images/Cloud0.png");
		break;
	case 1:
		textureCloud.loadFromFile("Images/Cloud1.png");
		break;
	case 2:
		textureCloud.loadFromFile("Images/Cloud2.png");
		break;
	}
	SizeX = textureCloud.getSize().x / Scale;
	setOrigin(0,0);
	setPosition((float)((rand() % win.getSize().x)),(float)((rand() % 400) - 20));
}

Cloud::~Cloud(){}

void Cloud::Draw(sf::RenderWindow &win,float Speed)
{
	if (getPosition().x > win.getSize().x + SizeX)
		setPosition(win.getSize().x  + SizeX,getPosition().y);
	setTexture(textureCloud);
	setScale(FlipX/Scale,FlipY/Scale);
	setRotation((float)Angle);
	setPosition(getPosition().x - Speed/Wind,getPosition().y);
	win.draw(*this);
}