#include "Birds.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

Birds::Birds()
{
}

Birds::~Birds()
{
}

Birds::Birds(int Id,int width,int height)
{
	ID = 1;
	Type =rand() % 3;
	if((rand() % 2 == 0)) Direction = -1; else Direction = 1;
	frameCount = 0.0f;
	State = 0;
	textureBird.loadFromFile("Images/Bird.png");
	textureHitBird.loadFromFile("Images/Hit.png");
	textureDeadBird.loadFromFile("Images/Dead.png");
	setPosition((float)(rand() % width + 200),(float)(height-335));
}

void Birds::Draw(sf::RenderWindow &win,float Speed)
{
	frameCount += Speed/3;
	if (frameCount >=3) frameCount = 0.0f;
	switch (State)
	{
	case 0:  //Life
		setTexture(textureBird);
		setTextureRect(sf::IntRect((int)frameCount*35,Type*33,35,33));
		setOrigin(17,16);
		setScale((float)Direction,1.0f);
		setPosition(getPosition().x + Direction * Speed * (Type+1),getPosition().y - Speed * (Type+1));
		break;
	case 1:  // Hit
		setTexture(textureHitBird);
		setTextureRect(sf::IntRect(0,Type*35,36,35));
		setOrigin(18,17);
		setScale((float)Direction,1.0f);
		if (frameCount >= 2)
		{
			frameCount = 0;
			SetState(2);
		}
		//setPosition(getPosition().x + Direction * Speed * (Type+1),getPosition().y - Speed * (Type+1));
		break;
	case 2:  // Dead
		setTexture(textureDeadBird);
		setTextureRect(sf::IntRect(((int)frameCount % 2)*24,Type*35,24,35));
		setOrigin(12,17);
		setScale((float)Direction,1.0f);
		setPosition(getPosition().x,getPosition().y + Speed*5);
		break;
	}
	win.draw(*this);
}

void Birds::SetState(int state)
{
	State = state;
}
int Birds::GetState()
{
	return State;
}
int Birds::GetScore()
{
	return Type+1;
}