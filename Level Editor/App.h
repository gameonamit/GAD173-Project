#pragma once

#include "SFML/Graphics.hpp"
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
	sf::RectangleShape  Bricks[ROWS][COLS];

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

public:
	App(const char* title, int screenWidth, int screenHeight, int screenBpp);
	~App();

	bool Init();
	void HandleEvents();
	void Draw();
	void Update();
	void Run();
};