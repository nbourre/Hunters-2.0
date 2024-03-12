#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Tree : public sf::Sprite
{
private:
	int Type;
	int Direction;
	sf::Texture textureTree;
public:
	Tree();
	~Tree();
	Tree(sf::RenderWindow &win,int);
	void Draw(sf::RenderWindow &win);
	int GetType();
	int GetDirection();
};