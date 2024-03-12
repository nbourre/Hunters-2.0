#pragma once
#include <SFML/Graphics.hpp>
#include <list>

using namespace std;

class Menu
{
private:
	sf::Text titleMenu;
	list<sf::Text> itemsMenu;
	int textSize;
	sf::Font fontMenu;
public:
	Menu();
	~Menu();
	Menu(int,string);
	void AddItem(string);
	void Draw(sf::RenderWindow &win);
	int GetItemSelected(sf::RenderWindow &win);
};