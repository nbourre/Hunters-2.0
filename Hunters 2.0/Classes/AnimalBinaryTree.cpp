#include "AnimalBinaryTree.hpp"

BTree::BTree()
{
  root=NULL;
}

BTree::~BTree()
{
	DestroyTree();
}

void BTree::Insert(int key,int aniType,int dir, Node *current)
{
	if(key< current->key_value)
	{
		if(current->left!=NULL)
			Insert(key, aniType,dir, current->left);
		else
		{
			current->left=new Node;
			current->left->key_value=key;
			current->left->animalType = aniType;
			current->left->direction = dir;
			if (dir == 1)
				current->setPosition(-50,700);
			else
				current->setPosition(1200,700);
			current->left->currentFrame = 0.0f;
			current->left->left=NULL;
			current->left->right=NULL;
		}  
	}
	else if(key>=current->key_value)
	{
		if(current->right!=NULL)
			Insert(key,aniType,dir, current->right);
		else
		{
			current->right=new Node;
			current->right->key_value=key;
			current->right->animalType = aniType;
			current->right->direction = dir;
			if (dir == 1)
				current->setPosition(-50,700);
			else
				current->setPosition(1200,700);
			current->right->currentFrame = 0.0f;
			current->right->left=NULL;    //Sets the left child of the child node to null
			current->right->right=NULL;   //Sets the right child of the child node to null
		}
	}
}

void BTree::DestroyTree(Node *current)
{
  if(current!=NULL)
  {
    DestroyTree(current->left);
    DestroyTree(current->right);
    delete current;
  }
}

void BTree::UpdateTree(Node* current,float speed, Animal ani[])
{
  if(current!=NULL)
  {
    UpdateTree(current->left,speed, ani);
    UpdateTree(current->right,speed, ani);
	current->currentFrame += (speed * ani[current->animalType].GetImagePerSecond()/ani[current->animalType].GetImageCount());
	if(current->currentFrame >= ani[current->animalType].GetImageCount())
		current->currentFrame = 0.0f;
	current->setPosition(current->getPosition().x + ani[current->animalType].GetDirection() * speed * ani[current->animalType].GetSpeedPerSecond()*(current->getPosition().y)/700,current->getPosition().y);
  }
}

void BTree::DrawTree(sf::RenderWindow &win,Node* current, Animal ani[])
{
	if (current != NULL)
	{
		DrawTree(win,current->left, ani);
		current->setTexture(ani[current->animalType]);
		current->setOrigin(0,ani[current->animalType].getSize().y/ani[current->animalType].GetImageCount());
		current->setPosition(current->getPosition().x,current->key_value);
		int height= ani[current->animalType].getSize().y/ani[current->animalType].GetImageCount();
		current->setTextureRect(sf::IntRect(0,height * ((int) current->currentFrame),ani[current->animalType].getSize().x,height));
		float scale = (float)current->key_value;
		scale = scale / win.getSize().y / 2;
		current->setScale(0.5f+scale,0.5f+scale);
		win.draw(*current);
		DrawTree(win,current->right, ani);
	}
}

void BTree::Insert(int key,int aniType,int dir)
{
	if(root!=NULL)
		Insert(key, aniType, dir, root);
	else
	{
		root=new Node;
		root->key_value=key;
		root->animalType = aniType;
		root->direction = dir;
		if (dir == 1)
			root->setPosition(-50,700);
		else
			root->setPosition(1200,700);
		root->currentFrame = 0.0f;
		root->left=NULL;
		root->right=NULL;
	}
}

void BTree::DestroyTree()
{
  DestroyTree(root);
}

void BTree::UpdateTree(float speed, Animal ani[])
{
	UpdateTree(root,speed,ani);
}

void BTree::DrawTree(sf::RenderWindow &win,Animal ani[])
{
	DrawTree(win,root, ani);
}
