#pragma once
#include "SFML/Graphics.hpp"
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>

//Global Variables
//Declare an array of bricks
const int ROWS = 4;
const int COLS = 8;

class App
{
private:
	float               deltaTime;
	sf::Clock           clock;
	sf::Clock           newClock;
	sf::Event			event;
	sf::View			view;
	sf::RenderWindow	window;

	//Smoke Animaiton
	sf::Texture smoke_Texture;
	sf::IntRect smokeAnimRect;
	sf::Sprite smokeAnimSprite[ROWS][COLS];
	bool smokeAnimation[ROWS][COLS];

public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);
	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();
	void PlaySmokeAnimation(int x, int y);
};

