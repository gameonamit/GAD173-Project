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
	std::fstream myfile;
	//std::ifstream newFile;
	std::ofstream outfile;
	

	int buttonLength;
	int buttonHeight;

	sf::RectangleShape playButton;
	sf::Text playBtnText;

	sf::RectangleShape customLevelButton;
	sf::Text customLevelBtnText;

	sf::RectangleShape quitButton;
	sf::Text quitBtnText;
	bool levelPaused;
	bool gameOver;
	bool gameWon;
	bool customLevel;

	sf::Text gameOverText;
	sf::Text menuBtnText;
	sf::RectangleShape menuButton;

	//Custom Level Menu
	sf::Text customMenuBtnText;
	sf::RectangleShape customMenuButton;
	sf::Text customPlayBtnText;
	sf::RectangleShape customPlayButton;

	sf::Text gameWonText;
	sf::Text gameWonScoreText;
	int noOfBricks;
	int x[ROWS][COLS] = { };

	// sound
	sf::SoundBuffer ballBounceBuffer;
	sf::SoundBuffer blockHitBuffer;
	sf::SoundBuffer buttonClickBuffer;

	sf::Sound ballBounce;
	sf::Sound blockHit;
	sf::Sound buttonClick;

	sf::Texture bgTexture;
	sf::Sprite bgSprite;
	sf::Texture blockTexture;
	sf::Texture paddleTexture;
	sf::Texture ballTexture;
	sf::Texture buttonCoverTexture;

	sf::Sprite lives1;
	sf::Sprite lives2;
	sf::Sprite lives3;

	int livesLeft;


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
	void InitializeCustomArrayOfBricks();
};


// Load the font from a file

