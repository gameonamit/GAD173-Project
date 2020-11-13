#pragma once
#include "SFML/Graphics.hpp"
#include <iostream>
#include <fstream>
#include <string>

//Global Variables
//Declare an array of bricks
const int ROWS = 3;
const int COLS = 7;

class App
{
private:
	float               deltaTime;
	sf::Clock           clock;
	sf::Event			event;
	sf::View			view;
	sf::RenderWindow	window;

	// Other data members here
	float				radius;
	sf::CircleShape		Ball;
    sf::RectangleShape  paddle;

	//Pointer Array of Bricks
	sf::RectangleShape **b;

	// Check if brick has been hit
	bool                collidable[ROWS][COLS];

	// Variables
	float               paddlespeed;
	float               paddleWidth;
	float               paddleHeight;

	float               xBallSpeed;
	float               yBallSpeed;
	float               pad;

	float               edgeGap;
	float               gap;
	float               brickLength;
	float               brickHeight;

	int                 score;
	sf::Font font;
	sf::Text atext;
	// declare
	std::ofstream myfile;
	std::ifstream newfile;

	int buttonLength;
	int buttonHeight;

	sf::RectangleShape playButton;
	sf::Text playBtnText;

	sf::RectangleShape customLevelButton;
	sf::Text customLevelBtnText;

	sf::RectangleShape quitButton;
	sf::Text quitBtnText;
	bool levelPaused;

	//Pointers


public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);
	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();
	void StartLevel();
	void InitializeArrayOfBricks();
};


// Load the font from a file

