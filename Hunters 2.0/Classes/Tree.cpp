#include "Tree.hpp"
#include <SFML/Graphics.hpp>

using namespace std;

Tree::Tree()
{
}

Tree::~Tree()
{
}

Tree::Tree(sf::RenderWindow &win,int Y)
{
	Type = rand() % 5 + 1;
	string filename = "Images/Tree0.png";
	filename[11]=48+Type;
	textureTree.loadFromFile(filename);
	setTexture(textureTree);
	setOrigin(0.0f,(float)textureTree.getSize().y);
	if((rand() % 2 == 0)) Direction = -1; else Direction = 1;
	setScale(Direction * 0.5f,0.5f);
	setPosition((float)(rand() % win.getSize().x),(float)Y);
}

void Tree::Draw(sf::RenderWindow &win)
{
	setTexture(textureTree);
	setOrigin(0.0f,(float)textureTree.getSize().y);
	setScale(Direction * 0.5f,0.5f);
	setPosition(getPosition().x,getPosition().y);
	win.draw(*this);
}
int Tree::GetType()
{
	return Type;
}

int Tree::GetDirection()
{
	return Direction;
}