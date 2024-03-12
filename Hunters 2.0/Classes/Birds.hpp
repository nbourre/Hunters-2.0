#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Birds : public sf::Sprite
{
private:
	int ID;
	int Type;
	int Direction;
	float frameCount;
	int State;
	sf::Texture textureBird;
	sf::Texture textureHitBird;
	sf::Texture textureDeadBird;
public:
	Birds();
	~Birds();
	Birds(int,int,int);
	void Draw(sf::RenderWindow &win,float);
	void SetState(int);
	int GetState();
	int GetScore();
};