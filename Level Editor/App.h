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

	// Ball
	float				radius;
	sf::CircleShape		Ball;

	//Paddle
	sf::RectangleShape  paddle;

	//Pointer Array of Bricks
	sf::RectangleShape** b;

	sf::RectangleShape playButton;
	sf::RectangleShape customLevelButton;
	sf::RectangleShape quitButton;
	sf::RectangleShape menuButton;
	sf::RectangleShape customMenuButton;
	sf::RectangleShape customPlayButton;
	sf::RectangleShape enablerMenuButton;
	sf::RectangleShape redMenuButton;
	sf::RectangleShape blueMenuButton;
	sf::RectangleShape purpleMenuButton;
	sf::RectangleShape greenMenuButton;

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
	int					buttonLength;
	int					buttonHeight;
	int					noOfBricks;
	int					livesLeft;
	int					x[ROWS][COLS] = { };

	bool				levelPaused;
	bool				gameOver;
	bool				gameWon;
	bool				customLevel;
	bool                collidable[ROWS][COLS];
	// Check if brick has been hit

	bool enablerMenuSelected;
	bool redMenuSelected;
	bool blueMenuSelected;
	bool purpleMenuSelected;
	bool greenMenuSelected;
	//Color Select Menus

	//Font
	sf::Font font;

	//Text Variables
	sf::Text atext;
	sf::Text quitBtnText;
	sf::Text playBtnText;
	sf::Text customLevelBtnText;
	sf::Text gameOverText;
	sf::Text menuBtnText;
	sf::Text customMenuBtnText;
	sf::Text customPlayBtnText;
	sf::Text gameWonText;
	sf::Text gameWonScoreText;

	// Declare Files
	std::fstream myfile;
	std::ofstream outfile;
	std::fstream myColorFile;
	std::ofstream outColorFile;

	public: enum BlockColors {Blue, Red, Purple, Green};
	//Declearing Colors

    int tempColor[ROWS][COLS] = { };
	BlockColors blockColor[ROWS][COLS] = { };
	//Initializing Block Color

	//PowerUp Variables
	sf::Texture increasePaddlePowerUpTexture;
	sf::Texture increaseScorePowerUpTexture;
	sf::Texture firePowerUpTexture;
	
	sf::Sprite increasePaddlePowerUp;
	sf::Sprite increaseScorePowerUp;
	sf::Sprite firePowerUp;

	bool increasePaddleSpawned;
	bool increaseScoreSpawned;
	bool firePowerUpSpawned;

	bool IncreasePaddleActivated;
	bool IncreaseScoreActivated;
	bool FirePowerUpActivated;

	sf::Clock clock_IncreasePaddle;
	sf::Clock clock_FirePowerUp;
	sf::Clock clock_IncreaseScore;
	//**---------------------------**
	
	// Sound & Sound Buffers
	sf::SoundBuffer ballBounceBuffer;
	sf::SoundBuffer blockHitBuffer;
	sf::SoundBuffer buttonClickBuffer;
	sf::SoundBuffer powerUpBuffer;

	sf::Sound ballBounce;
	sf::Sound blockHit;
	sf::Sound buttonClick;
	sf::Sound powerUpSound;

	// Textures
	sf::Texture bgTexture;
	sf::Texture paddleTexture;
	sf::Texture ballTexture;
	sf::Texture fireBallTexture;
	sf::Texture buttonCoverTexture;
	sf::Texture smoke_Texture;

	//Block Textures
	sf::Texture blueBlockTexture;
	sf::Texture redBlockTexture;
	sf::Texture purpleBlockTexture;
	sf::Texture greenBlockTexture;

	//Menu Textures
	sf::Texture enablerMenuTexture;
	sf::Texture redMenuTexture;
	sf::Texture blueMenuTexture;
	sf::Texture purpleMenuTexture;
	sf::Texture greenMenuTexture;
	sf::Texture enablerMenuOnclickTexture;
	sf::Texture redMenuOnclickTexture;
	sf::Texture blueMenuOnclickTexture;
	sf::Texture purpleMenuOnclickTexture;
	sf::Texture greenMenuOnclickTexture;

	// Sprites
	sf::Sprite bgSprite;
	sf::Sprite lives1;
	sf::Sprite lives2;
	sf::Sprite lives3;

	//Smoke Animaiton
	sf::IntRect smokeAnimRect[ROWS][COLS];
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
	void StartLevel();
	void InitializeArrayOfBricks();
	void InitializeCustomArrayOfBricks();
	void ResetAllMenuButtons();
	void GenerateRandomPowerUp(float x, float y);
	void StartIncreasePaddlePowerUp();
	void StartIncreaseScorePowerUp();
	void StartFirePowerUp();
};

