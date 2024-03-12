#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

class TypeAnimal : public sf::Texture
{
private:
	int imageCount;
	int timePerImage;
	int speedPerImage;
	int direction;
public:
	TypeAnimal();
	~TypeAnimal();
	TypeAnimal(string,int,int,int,int);
	int GetImageCount();
	int GetTimePerImage();
	int GetSpeedPerImage();
	int GetDirection();
};

class Animal : public sf::Sprite
{
private:
	int ID;
	int Direction;
	float CptFrame;
	sf::Color couleur;
public:
	TypeAnimal Type;
	Animal();
	Animal(int, int, TypeAnimal,sf::RenderWindow &win);
	~Animal();
	void Draw(sf::RenderWindow &win, float);
};