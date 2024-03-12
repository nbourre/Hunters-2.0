#include "Gamers.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

Gamers::Gamers()
{
	Role = "CLIENT";
	textureLargeCible.loadFromFile("Images/LargeTarget.png");
	textureCible.loadFromFile("Images/Target.png");
	Score = 0;
	GodMode = false;
}

Gamers::~Gamers()
{
}

Gamers::Gamers(sf::Color color)
{
	Role = "CLIENT";
	textureLargeCible.loadFromFile("Images/LargeTarget.png");
	textureCible.loadFromFile("Images/Target.png");
	radius = textureCible.getSize().x / 2.0f;
	Score = 0;
	GodMode = false;
	colorCible = color;
}

void Gamers::SetPosition(float X, float Y)
{
	posX = X;
	posY = Y;
}

sf::Vector2f Gamers::GetPosition()
{
	sf::Vector2f position(posX,posY);
	return position;
}

float Gamers::GetRadius()
{
	return radius;
}
void Gamers::Draw(sf::RenderWindow &win)
{
	sf::Sprite spriteCible;
	if(GodMode)
	{
		spriteCible.setTexture(textureLargeCible);
		radius = (float)(textureLargeCible.getSize().x/2);
		spriteCible.setOrigin((float)(textureLargeCible.getSize().x/2),(float)(textureLargeCible.getSize().y/2));
	}
	else
	{
		spriteCible.setTexture(textureCible);
		radius = (float)(textureCible.getSize().x/2);
		spriteCible.setOrigin((float)(textureCible.getSize().x/2),(float)(textureCible.getSize().y/2));
	}
	spriteCible.setPosition(posX,posY);
	spriteCible.setColor(colorCible);
	win.draw(spriteCible);
}

void Gamers::IncScore(int value)
{
	Score += value;
}

int Gamers::GetScore()
{
	return Score;
}

void Gamers::SetGodMode(bool value)
{
	GodMode = value;
}

bool Gamers::GetGodMode()
{
	return GodMode;
}