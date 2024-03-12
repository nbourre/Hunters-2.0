#include <iostream>
#include <sstream>
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <thread>
#include "Classes/Gamers.hpp"
#include "Classes/Menu.hpp"
#include "Classes/NetworkManager.hpp"
#include "Classes/FrameCalculator.hpp"
#include "Classes/Cloud.hpp"
#include "Classes/Birds.hpp"
#include "Classes/Tree.hpp"
#include "Classes/Animal.hpp"

#include <SFML/Audio.hpp>

using namespace sf;
using namespace std;

//Globals variables
RenderWindow window;
Gamers LocalGamer;
Gamers NetworkGamer;
Menu menu(48, "OpenSans-Regular.ttf");
bool menuIsOn = true;
FrameCalculator frameCalculator;
Texture textureCloud[3];
Texture textureTree[6];
Texture textureGrass;
SoundBuffer soundGun;
SoundBuffer soundFirstBlood;
SoundBuffer soundMonsterKill;
SoundBuffer soundHeadShot;
Sound FirstBlood;
Sound MonsterKill;
Sound shoot;
Font font;
list<Cloud> Clouds;
list<Birds> birds;
list<Tree> Trees;
list<Animal> Animals;
TypeAnimal typeAnimal[6];

string GamingMode = "";
string Role;
bool ProgramIsRunning = true;

void GenerateSound()
{
	SoundBuffer sounds[14];
	Sound sound;
	srand((int)time(NULL));
	for (int cpt = 0;cpt < 14;cpt++)
	{
		char FileName[40] = "Sounds/A.wav";
		FileName[7] = 'A' + cpt;
		sounds[cpt].loadFromFile(FileName);
	}
	while (ProgramIsRunning)
	{
		sf::sleep(sf::seconds((float)(rand() % 10 + 2)));
		sound.setBuffer(sounds[rand() % 14]);
		sound.setPosition((float)((rand() % 2) * 1024), 384.f, 1.f);
		sound.setAttenuation(0.f);
		sound.play();
	}
}
sf::Thread threadAmbiance(&GenerateSound);

void GenerateCloud()
{
	srand((int)time(NULL));
	int idGenerator = 0;
	for (idGenerator = 0;idGenerator < 5;idGenerator++)
	{
		Cloud newCloud = Cloud(idGenerator, window);
		Clouds.push_back(newCloud);
	}
	while (ProgramIsRunning)
	{
		Cloud newCloud = Cloud(idGenerator);
		Clouds.push_back(newCloud);
		sf::Time WaitingTime = sf::seconds((float)(rand() % 10 + 10));
		sf::sleep(WaitingTime);
		idGenerator++;
	}
	Clouds.clear();
}
sf::Thread threadCloud(&GenerateCloud);

void GenerateBird()
{
	srand((int)time(NULL));
	int idGenerator = 0;
	while (ProgramIsRunning)
	{
		Birds newBird = Birds(idGenerator, window.getSize().x - 400, window.getSize().y);
		birds.push_back(newBird);
		sf::Time WaitingTime = sf::seconds(8 / ((float)(rand() % 20 + 1.0f)));
		sf::sleep(WaitingTime);
		idGenerator++;
	}
	birds.clear();
}
sf::Thread threadBird(&GenerateBird);

void GenerateAnimal()
{
	srand((int)time(NULL));
	int idGenerator = 0;
	int Direction;
	while (ProgramIsRunning)
	{
		sf::Time WaitingTime = sf::seconds((float)(rand() % 5 + 2));
		sf::sleep(WaitingTime);
		int animalType = rand() % 6;
		if ((rand() % 2 == 0)) Direction = -1; else Direction = 1;
		Animal NewAnimal = Animal(idGenerator, Direction, typeAnimal[animalType], window);
		Animals.push_back(NewAnimal);
		idGenerator++;
	}
	Animals.clear();
}
sf::Thread threadAnimal(&GenerateAnimal);

void CreateForest()
{
	srand((int)time(NULL));
	for (int Cpt = (int)window.getSize().y - 320;Cpt < (int)window.getSize().y - 200;Cpt += 1)
	{
		if (rand() % 2 == 0)
		{
			Tree newTree = Tree(window, Cpt);
			Trees.push_back(newTree);
		}
	}
}

void ManageMenu(bool& menuIsOn)
{
	switch (menu.GetItemSelected(window))
	{
	case 0: // Single Player
		window.setMouseCursorVisible(false);
		GamingMode = "SINGLE_USER";
		threadAmbiance.launch();
		threadBird.launch();
		threadAnimal.launch();
		menuIsOn = false;
		break;
	case 1: // Exit Game
		window.close();
		break;
	}
}

void ShowTarget(sf::RenderWindow& win)
{
	LocalGamer.SetPosition((float)sf::Mouse::getPosition(win).x, (float)sf::Mouse::getPosition(win).y);
	if ((Keyboard::isKeyPressed(Keyboard::LControl)) && (Keyboard::isKeyPressed(Keyboard::LShift))&& (Keyboard::isKeyPressed(Keyboard::Space)))
	{
		LocalGamer.SetGodMode(true);
	}
	else
	{
		LocalGamer.SetGodMode(false);
	}
	LocalGamer.Draw(win);
}

bool CloudIsOut(Cloud& cloud)
{
	return(cloud.getPosition().x < -1000);
}

void DrawCloud(sf::RenderWindow& win, float Speed)
{
	for (list<Cloud>::iterator CurrentCloud = Clouds.begin(); CurrentCloud != Clouds.end(); CurrentCloud++)
	{
		CurrentCloud->Draw(win, Speed);
	}
	Clouds.remove_if(CloudIsOut);
}

bool AnimalIsOut(Animal& animal)
{
	return((animal.getPosition().x < -100) || (animal.getPosition().x > window.getSize().x + 100));
}

void DrawAnimal(sf::RenderWindow& win, float Speed)
{
	for (list<Animal>::iterator CurrentAnimal = Animals.begin(); CurrentAnimal != Animals.end(); CurrentAnimal++)
	{
		CurrentAnimal->Draw(win, Speed);
	}
	Animals.remove_if(AnimalIsOut);
}

void DrawForest(sf::RenderWindow& win)
{
	for (list<Tree>::iterator CurrentTree = Trees.begin(); CurrentTree != Trees.end(); CurrentTree++)
	{
		CurrentTree->Draw(win);
	}
}

void DrawBackground(sf::RenderWindow& win, float speed)
{
	sf::Sprite sprite;
	sprite.setTexture(textureGrass);
	sprite.setOrigin(0.0f, (float)textureGrass.getSize().y);
	sprite.setPosition(0.0f, (float)win.getSize().y);
	win.draw(sprite);
	DrawForest(win);
	DrawAnimal(win, speed);
}

bool BirdIsOut(Birds& bird)
{
	return((bird.getPosition().y < -15) || (bird.getPosition().y > window.getSize().y - 300));
}

void DrawBirds(sf::RenderWindow& win, float Speed)
{
	for (list<Birds>::iterator CurrentBird = birds.begin(); CurrentBird != birds.end(); CurrentBird++)
	{
		CurrentBird->Draw(win, Speed);
	}
	birds.remove_if(BirdIsOut);
}

void DrawScore(sf::RenderWindow& win)
{
	std::ostringstream osStringScore;
	osStringScore << "SCORE : " << LocalGamer.GetScore();
	sf::Text textScore;
	textScore.setString(osStringScore.str());
	textScore.setFont(font);
	textScore.setFillColor(Color(255, 0, 0));
	textScore.setOutlineColor(Color(255, 0, 0));
	textScore.setPosition(0, 0);
	win.draw(textScore);
}

float Distance(float X1, float Y1, float X2, float Y2)
{
	return (float)sqrt((X2 - X1) * (X2 - X1) + (Y2 - Y1) * (Y2 - Y1));
}

void CheckHit(RenderWindow& win)
{
	float radius = LocalGamer.GetRadius();
	int totalPoint = 0;
	for (list<Birds>::iterator CurrentBird = birds.begin(); CurrentBird != birds.end(); CurrentBird++)
	{
		if ((Distance(CurrentBird->getPosition().x, CurrentBird->getPosition().y, LocalGamer.GetPosition().x, LocalGamer.GetPosition().y) <= radius) && (CurrentBird->GetState() == 0))
		{
			if (LocalGamer.GetScore() == 0)
			{
				FirstBlood.play();
			}
			totalPoint += CurrentBird->GetScore();
			LocalGamer.IncScore(CurrentBird->GetScore());
			CurrentBird->SetState(1);
		}
	}
	if (totalPoint >= 20)
	{
		MonsterKill.play();
	}
}

void InitResource()
{
	window.create(sf::VideoMode(sf::VideoMode::getDesktopMode()),"", sf::Style::Fullscreen);
	menu.AddItem("Commencer");
	menu.AddItem("Quitter");
	font.loadFromFile("OpenSans-Regular.ttf");
	typeAnimal[0] = TypeAnimal("Images/Cheetah.png", 8, 3, 10, 1);
	typeAnimal[1] = TypeAnimal("Images/Deer.png", 18, 3, 7, 1);
	typeAnimal[2] = TypeAnimal("Images/Tiger.png", 16, 4, 2, 1);
	typeAnimal[3] = TypeAnimal("Images/WhiteHorse.png", 12, 4, 3, 1);
	typeAnimal[4] = TypeAnimal("Images/Dalmatien.png", 7, 4, 9, 1);
	typeAnimal[5] = TypeAnimal("Images/Joke.png", 6, 3, 9, 1);
	textureGrass.loadFromFile("Images/Grass.png");
	soundGun.loadFromFile("Sounds/357mag.wav");
	soundFirstBlood.loadFromFile("Sounds/firstblood.wav");
	soundHeadShot.loadFromFile("Sounds/Headshot.wav");
	soundMonsterKill.loadFromFile("Sounds/monsterkill.wav");
	shoot.setBuffer(soundGun);
	FirstBlood.setBuffer(soundFirstBlood);
	MonsterKill.setBuffer(soundMonsterKill);
	CreateForest();
}

void CheckLocalEvent(sf::RenderWindow& win)
{
	sf::Event event;
	while (win.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			win.close();
			break;
		case sf::Event::MouseButtonPressed:
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				if (menuIsOn)
					ManageMenu(menuIsOn);
				else
				{
					shoot.setVolume(30);
					shoot.play();
					CheckHit(win);
				}
			}
		case sf::Event::KeyPressed:
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				win.close();
			break;
		default:
			break;
		}
	}
}

int main()
{
	InitResource();
	frameCalculator.Reset();
	threadCloud.launch();
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		frameCalculator.CalculateFrameRate();
		CheckLocalEvent(window);
		window.clear(sf::Color(50, 100, 255));
		DrawCloud(window, frameCalculator.GetSpeedFactor());
		if (menuIsOn)
		{
			DrawBackground(window, frameCalculator.GetSpeedFactor());
			menu.Draw(window);
		}
		else
		{
			DrawBirds(window, frameCalculator.GetSpeedFactor());
			DrawBackground(window, frameCalculator.GetSpeedFactor());
			DrawScore(window);
			ShowTarget(window);
		}
		window.display();
	}
	threadAmbiance.terminate();
	threadCloud.terminate();
	threadBird.terminate();
	threadAnimal.terminate();
	ProgramIsRunning = false;
	return 0;
}