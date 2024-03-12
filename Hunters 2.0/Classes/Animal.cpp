#include "Animal.hpp"

TypeAnimal::TypeAnimal()
{
}
TypeAnimal::~TypeAnimal()
{
}
TypeAnimal::TypeAnimal(std::string fileName, int imgCount, int imgPerSecond, int speed, int dir)
{
	loadFromFile(fileName);
	imageCount = imgCount;
	timePerImage = imgPerSecond;
	speedPerImage = speed;
	direction = dir;
}

int TypeAnimal::GetImageCount()
{
	return(imageCount);
}

int TypeAnimal::GetTimePerImage()
{
	return(timePerImage);
}

int TypeAnimal::GetSpeedPerImage()
{
	return(speedPerImage);
}

int TypeAnimal::GetDirection()
{
	return(direction);
}

Animal::Animal()
{
}

Animal::~Animal()
{
}

Animal::Animal(int Id, int Dir, TypeAnimal type, sf::RenderWindow& win)
{
	ID = Id;
	Direction = Dir;
	CptFrame = 0;
	Type = type;
	setTexture(Type);
	if (Direction == 1)
		setPosition(-100, win.getSize().y - (float)(rand() % 200));
	else
		setPosition((float)(win.getSize().x + 100), (float)(win.getSize().y - 275 + rand() % 200));
}

void Animal::Draw(sf::RenderWindow& win, float Speed)
{
	setTexture(Type);
	setTextureRect(sf::IntRect(0, (int)CptFrame * Type.getSize().y / Type.GetImageCount(), Type.getSize().x, Type.getSize().y / Type.GetImageCount()));
	CptFrame += Speed / Type.GetTimePerImage();
	if (CptFrame >= Type.GetImageCount())
		CptFrame = 0;
	if (Direction == -1)
		setScale(-1, 1);
	setPosition(getPosition().x + (Direction * Speed * Type.GetSpeedPerImage()), getPosition().y);
	win.draw(*this);
}