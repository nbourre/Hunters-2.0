#include "Menu.hpp"
#include <list>
using namespace sf;
using namespace std;

Menu::Menu()
{
}
Menu::~Menu()
{
	itemsMenu.clear();
}
Menu::Menu(int size, string fontName)
{
	textSize = size;
	fontMenu.loadFromFile(fontName);
}
void Menu::AddItem(string text)
{
	Text item;
	item.setString(text);
	item.setFont(fontMenu);
	item.setCharacterSize(textSize);
	item.setFillColor(Color(0, 255, 255));
	item.setOutlineColor(Color(0, 255, 255));
	itemsMenu.push_back(item);
}
void Menu::Draw(RenderWindow& win)
{
	float itemHeight = (float)(textSize) * 1.5f;
	float menuHeight = itemHeight * itemsMenu.size();
	float startMenu = (float)(win.getSize().y / 2 - menuHeight / 2);
	int count = 0;
	for (list<Text>::iterator currentItem = itemsMenu.begin(); currentItem != itemsMenu.end(); currentItem++)
	{
		currentItem->setCharacterSize(textSize + (GetItemSelected(win) == count) * textSize / 2);
		currentItem->setOrigin(currentItem->getLocalBounds().width / 2, currentItem->getLocalBounds().height);
		currentItem->setPosition(win.getSize().x / 2.0f, startMenu + (float)(count)*itemHeight + itemHeight / 2.0f);
		win.draw(*currentItem);
		count++;
	}
}
int Menu::GetItemSelected(RenderWindow& win)
{
	int itemSelected = -1;
	int count = 0;
	float mouseX = Mouse::getPosition(win).x;
	float mouseY = Mouse::getPosition(win).y;
	for (list<Text>::iterator currentItem = itemsMenu.begin(); currentItem != itemsMenu.end(); currentItem++)
	{
		float width = currentItem->getLocalBounds().width;
		float height = currentItem->getLocalBounds().height;
		float X = currentItem->getPosition().x;
		float Y = currentItem->getPosition().y;
		if ((mouseX >= X - width / 2) && (mouseX <= X + width / 2) && (mouseY >= Y - height / 2) && (mouseY <= Y + height / 2))
			itemSelected = count;
		count++;
	}
	return itemSelected;
}