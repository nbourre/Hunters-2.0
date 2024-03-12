#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animal.hpp"

struct Node : public sf::Sprite
{
	int key_value;
	int animalType;
	int direction;
	float currentFrame;
	Node *left;
	Node *right;
};

class BTree
{
	private:
		void UpdateTree(Node *current,float speed, Animal ani[]);
		void DrawTree(sf::RenderWindow &win,Node *current, Animal[]);
        void DestroyTree(Node *current);
        void Insert(int, int, int, Node *current);       
        Node *root;
	public:
        BTree();
        ~BTree();
        void Insert(int,int,int);
        void DestroyTree();
		void UpdateTree(float, Animal[]);
		void DrawTree(sf::RenderWindow &win,Animal[]);
};