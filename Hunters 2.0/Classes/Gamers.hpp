#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class Gamers
{
private:
	string Role;
	float posX;
	float posY;
	sf::Texture textureCible;
	sf::Texture textureLargeCible;
	sf::Color colorCible;
	int Score;
	float radius;
	bool GodMode;
public:
	Gamers();
	~Gamers();
	Gamers(sf::Color);
	float GetRadius();
	void SetPosition(float,float);
	sf::Vector2f GetPosition();
	void Draw(sf::RenderWindow &win);
	void IncScore(int);
	int GetScore();
	void SetGodMode(bool);
	bool GetGodMode();
};