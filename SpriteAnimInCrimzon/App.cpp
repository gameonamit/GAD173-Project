#include "App.h"
#include <sfml/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// constructor
App::App(const char* title, int screenWidth, int screenHeight, int screenBpp)
{
	window.create(sf::VideoMode(screenWidth, screenHeight, screenBpp), title);
	window.setFramerateLimit(0);
	view = window.getDefaultView();
}

// destructor
App::~App()
{
}

bool App::Init()
{
	if (!smoke_Texture.loadFromFile("SmokeAnimation.png"))
	{
		std::cout << "Unable to load image" << std::endl;
	}

	smokeAnimRect.left = 5400;
	smokeAnimRect.top = 0;
	smokeAnimRect.height = 600;
	smokeAnimRect.width = 600;

	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			smokeAnimSprite[row][col].setTexture(smoke_Texture);
			smokeAnimSprite[row][col].setTextureRect(smokeAnimRect);
			smokeAnimSprite[row][col].scale(1, 1);
			smokeAnimation[row][col] = false;
		}
	}

	PlaySmokeAnimation(2, 2);

	return true;
}

void App::PlaySmokeAnimation(int row, int col)
{
	smokeAnimation[row][col] = true;
}

void App::Update()
{
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (smokeAnimation[col][row] == true)
			{
				if (newClock.getElapsedTime().asSeconds() > 0.08f)
				{
					smokeAnimRect.left -= 600;
					smokeAnimSprite[row][col].setTextureRect(smokeAnimRect);
					newClock.restart();
					std::cout << "Method Called" << std::endl;
				}
				if (smokeAnimRect.left == 0)
				{
					smokeAnimRect.left = 5400;
					smokeAnimation[col][row] = false;
					newClock.restart();
				}
			}
		}
	}
}

void App::Draw()
{
	window.clear();
	window.setView(view);

	//window.draw(smokeAnimSprite[2][2]);
	for (int row = 0; row < ROWS; ++row)
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (smokeAnimation[col][row] == true) 
			{
				window.draw(smokeAnimSprite[row][col]);
			}
		}
	}
	window.display();
}

void App::HandleEvents()
{
	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
}

void App::Run()
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			HandleEvents();
		}
		Update();
		Draw();
	}
}