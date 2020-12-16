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

	// open Files
	myfile.open("customLevel.txt", ios::out | ios::in);
	myColorFile.open("customLevelColors.txt", ios::out | ios::in);
}

// destructor
App::~App() 
{
	myfile.close();
	myColorFile.close();

	//Memory Allocation
	for (int i = 0; i < ROWS; ++i) {
		delete[] b[i];
	}
	delete[] b;
}

bool App::Init()
{
	gameOver = false;
	gameWon = false;
	customLevel = false;
	levelPaused = true;

	IncreasePaddleActivated = false;
	IncreaseScoreActivated = false;
	FirePowerUpActivated = false;

	increasePaddleSpawned = false;
	increaseScoreSpawned = false;
	firePowerUpSpawned = false;

	livesLeft = 3;
	noOfBricks = ROWS * COLS;
	
	//Button Properties
	buttonLength = 600;
	buttonHeight = 120;
	int buttonGap = 170;
	int topGap = 180;
	int textSize = 60;

	// Random speed of ball
	int sign = 2 * (rand() % 2) - 1;
	xBallSpeed = sign * (rand() % 100 + 500);
	yBallSpeed = -(rand() % 100 + 500);

	//Brick specifications
	brickLength = 150;
	brickHeight = 50;

	//Brick Array
	gap = 10;
	edgeGap = (window.getSize().x - COLS * brickLength - (COLS - 1) * gap) / 2;

	// that an object may move after a collision is detected
	pad = 20;

	//Set up Score text properties
	score = 0;
	atext.setFont(font);
	atext.setCharacterSize(80);
	atext.setStyle(sf::Text::Regular);
	atext.setFillColor(sf::Color::Green);
	atext.setPosition(50, 30);

	//Sprites and Textures
	if (!bgTexture.loadFromFile("Sprites/galaxy.jpg"))
	{
		std::cout << "BackGround sprite not loaded" << std::endl;
	}

	if (!blueBlockTexture.loadFromFile("Sprites/BlueBlock.png"))
	{
		std::cout << "blueBlockTexture sprite not loaded" << std::endl;
	}

	if (!redBlockTexture.loadFromFile("Sprites/RedBlock.png"))
	{
		std::cout << "redBlockTexture sprite not loaded" << std::endl;
	}

	if (!purpleBlockTexture.loadFromFile("Sprites/PurpleBlock.png"))
	{
		std::cout << "purpleBlockTexture sprite not loaded" << std::endl;
	}

	if (!greenBlockTexture.loadFromFile("Sprites/GreenBlock.png"))
	{
		std::cout << "greenBlockTexture sprite not loaded" << std::endl;
	}

	if (!paddleTexture.loadFromFile("Sprites/paddle.png"))
	{
		std::cout << "paddleTexture sprite not loaded" << std::endl;
	}

	if (!ballTexture.loadFromFile("Sprites/ball.png"))
	{
		std::cout << "ballTexture sprite not loaded" << std::endl;
	}

	if (!fireBallTexture.loadFromFile("Sprites/fireBall.png"))
	{
		std::cout << "fireBallTexture sprite not loaded" << std::endl;
	}

	if (!buttonCoverTexture.loadFromFile("Sprites/buttonCover.png"))
	{
		std::cout << "buttonCoverTexture not loaded" << std::endl;
	}

	if (!smoke_Texture.loadFromFile("Sprites/SmokeAnimation.png"))
	{
		std::cout << "Unable to load smoke_Texture" << std::endl;
	}

	if (!enablerMenuTexture.loadFromFile("Sprites/EnablerMenu.png"))
	{
		std::cout << "enablerMenuTexture sprite not loaded" << std::endl;
	}

	if (!enablerMenuOnclickTexture.loadFromFile("Sprites/EnablerMenuOnClick.png"))
	{
		std::cout << "enablerMenuOnclickTexture sprite not loaded" << std::endl;
	}

	if (!redMenuTexture.loadFromFile("Sprites/RedMenuBtn.png"))
	{
		std::cout << "redMenuTexture sprite not loaded" << std::endl;
	}

	if (!redMenuOnclickTexture.loadFromFile("Sprites/RedMenuBtnOnclick.png"))
	{
		std::cout << "redMenuOnclickTexture sprite not loaded" << std::endl;
	}

	if (!blueMenuTexture.loadFromFile("Sprites/BlueMenuBtn.png"))
	{
		std::cout << "blueMenuTexture sprite not loaded" << std::endl;
	}

	if (!blueMenuOnclickTexture.loadFromFile("Sprites/BlueMenuBtnOnclick.png"))
	{
		std::cout << "blueMenuOnclickTexture sprite not loaded" << std::endl;
	}

	if (!purpleMenuTexture.loadFromFile("Sprites/PurpleMenuBtn.png"))
	{
		std::cout << "purpleMenuTexture sprite not loaded" << std::endl;
	}

	if (!purpleMenuOnclickTexture.loadFromFile("Sprites/PurpleMenuBtnOnclick.png"))
	{
		std::cout << "purpleMenuOnclickTexture sprite not loaded" << std::endl;
	}

	if (!greenMenuTexture.loadFromFile("Sprites/GreenMenuBtn.png"))
	{
		std::cout << "greenMenuTexture sprite not loaded" << std::endl;
	}

	if (!greenMenuOnclickTexture.loadFromFile("Sprites/GreenMenuBtnOnclick.png"))
	{
		std::cout << "greenMenuOnclickTexture sprite not loaded" << std::endl;
	}

	if (!increasePaddlePowerUpTexture.loadFromFile("Sprites/IncreasePaddleSize.png"))
	{
		std::cout << "increasePaddlePowerUpTexture sprite not loaded" << std::endl;
	}

	if (!increaseScorePowerUpTexture.loadFromFile("Sprites/ExtraScore.png"))
	{
		std::cout << "increaseScorePowerUpTexture sprite not loaded" << std::endl;
	}

	if (!firePowerUpTexture.loadFromFile("Sprites/FirePowerUp.png"))
	{
		std::cout << "firePowerUpTexture sprite not loaded" << std::endl;
	}

	//BackGround Sprites
	bgSprite.setTexture(bgTexture);
	bgSprite.setScale((window.getSize().x) / bgSprite.getLocalBounds().width, (window.getSize().y) / bgSprite.getLocalBounds().height);

	// Ball Properties
	radius = 15;
	Ball.setRadius(radius);
	Ball.setPosition((window.getSize().x / 2) - radius, (window.getSize().y / 2) + 350);
	Ball.setTexture(&ballTexture);

	//Paddle
	paddleWidth = 200;
	paddleHeight = 30;
	paddlespeed = 1000;
	paddle.setSize(sf::Vector2f(paddleWidth, paddleHeight));
	paddle.setPosition(window.getSize().x / 2 - paddleWidth / 2, 0.95f * window.getSize().y - 60);
	paddle.setTexture(&paddleTexture);

	//Lives
	lives1.setTexture(ballTexture);
	lives1.setScale((Ball.getLocalBounds().width) / lives1.getLocalBounds().width, (Ball.getLocalBounds().width) / lives1.getLocalBounds().height);
	lives1.setPosition(window.getSize().x - 80, 30);

	lives2.setTexture(ballTexture);
	lives2.setScale((Ball.getLocalBounds().width) / lives2.getLocalBounds().width, (Ball.getLocalBounds().width) / lives2.getLocalBounds().height);
	lives2.setPosition(window.getSize().x - 140, 30);

	lives3.setTexture(ballTexture);
	lives3.setScale((Ball.getLocalBounds().width) / lives3.getLocalBounds().width, (Ball.getLocalBounds().width) / lives3.getLocalBounds().height);
	lives3.setPosition(window.getSize().x - 200, 30);

	//Font
	if (!font.loadFromFile("Fonts/myfont.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	//Play Button
	playButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	playButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight);
	playButton.setTexture(&buttonCoverTexture);

	playBtnText.setFont(font);
	playBtnText.setCharacterSize(textSize);
	playBtnText.setStyle(sf::Text::Regular);
	playBtnText.setFillColor(sf::Color::White);
	playBtnText.setString("Play");
	playBtnText.setPosition((window.getSize().x / 2) - (playBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + 20);

	//Custom Level Button
	customLevelButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	customLevelButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight + buttonGap);
	customLevelButton.setTexture(&buttonCoverTexture);

	customLevelBtnText.setFont(font);
	customLevelBtnText.setCharacterSize(textSize);
	customLevelBtnText.setStyle(sf::Text::Regular);
	customLevelBtnText.setFillColor(sf::Color::White);
	customLevelBtnText.setString("Custom Level");
	customLevelBtnText.setPosition((window.getSize().x / 2) - (customLevelBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + buttonGap + 20);

	//Quit Button
	quitButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	quitButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight + 2 * buttonGap);
	quitButton.setTexture(&buttonCoverTexture);

	quitBtnText.setFont(font);
	quitBtnText.setCharacterSize(textSize);
	quitBtnText.setStyle(sf::Text::Regular);
	quitBtnText.setFillColor(sf::Color::White);
	quitBtnText.setString("Quit");
	quitBtnText.setPosition((window.getSize().x / 2) - (quitBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + 2 * buttonGap + 20);

	//Menu Button
	menuButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	menuButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), (window.getSize().y / 2) + 170);
	menuButton.setTexture(&buttonCoverTexture);

	menuBtnText.setFont(font);
	menuBtnText.setCharacterSize(textSize);
	menuBtnText.setStyle(sf::Text::Regular);
	menuBtnText.setFillColor(sf::Color::White);
	menuBtnText.setString("Menu");
	menuBtnText.setPosition((window.getSize().x / 2) - (menuBtnText.getGlobalBounds().width / 2), (window.getSize().y / 2) + 170 + 20);

	//Game Over Text
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(160);
	gameOverText.setStyle(sf::Text::Regular);
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setString("Game Over");
	gameOverText.setPosition((window.getSize().x / 2) - (gameOverText.getGlobalBounds().width / 2), (window.getSize().y / 2) - 360);

	//Game Won Text
	gameWonText.setFont(font);
	gameWonText.setCharacterSize(160);
	gameWonText.setStyle(sf::Text::Regular);
	gameWonText.setFillColor(sf::Color::White);
	gameWonText.setString("Game Won");
	gameWonText.setPosition((window.getSize().x / 2) - (gameWonText.getGlobalBounds().width / 2), (window.getSize().y / 2) - 360);

	//Game Won Score Text
	gameWonScoreText.setFont(font);
	gameWonScoreText.setCharacterSize(textSize);
	gameWonScoreText.setStyle(sf::Text::Regular);
	gameWonScoreText.setFillColor(sf::Color::Green);
	gameWonScoreText.setString(std::to_string(score));
	gameWonScoreText.setPosition((window.getSize().x / 2) - (gameWonScoreText.getGlobalBounds().width / 2), (window.getSize().y / 2) - 60);

	//custom Menu Button
	customMenuButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	customMenuButton.setPosition((window.getSize().x / 2) - (customMenuButton.getGlobalBounds().width / 2) + 400, (window.getSize().y / 2) - (customMenuButton.getGlobalBounds().height / 2) + 300);
	customMenuButton.setTexture(&buttonCoverTexture);

	customMenuBtnText.setFont(font);
	customMenuBtnText.setCharacterSize(textSize);
	customMenuBtnText.setStyle(sf::Text::Regular);
	customMenuBtnText.setFillColor(sf::Color::White);
	customMenuBtnText.setString("Menu");
	customMenuBtnText.setPosition((window.getSize().x / 2) - (customMenuBtnText.getGlobalBounds().width / 2) + 400, (window.getSize().y / 2) - (customMenuBtnText.getGlobalBounds().height / 2) + 300 - 18);

	//Custom Play Button
	customPlayButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	customPlayButton.setPosition((window.getSize().x / 2) - (customPlayButton.getGlobalBounds().width / 2) - 400, (window.getSize().y / 2) - (customPlayButton.getGlobalBounds().height / 2) + 300);
	customPlayButton.setTexture(&buttonCoverTexture);

	customPlayBtnText.setFont(font);
	customPlayBtnText.setCharacterSize(textSize);
	customPlayBtnText.setStyle(sf::Text::Regular);
	customPlayBtnText.setFillColor(sf::Color::White);
	customPlayBtnText.setString("Play");
	customPlayBtnText.setPosition((window.getSize().x / 2) - (customPlayBtnText.getGlobalBounds().width / 2) - 400, (window.getSize().y / 2) - (customPlayBtnText.getGlobalBounds().height / 2) + 300 - 16);

	ResetAllMenuButtons();
	enablerMenuButton.setSize(sf::Vector2f(80, 80));
	enablerMenuButton.setPosition((window.getSize().x / 2) - (80 / 2) - 400, (window.getSize().y / 2) - (80 / 2));
	enablerMenuButton.setTexture(&enablerMenuOnclickTexture);

	enablerMenuSelected = true;

	//Sounds & SFX
	if (!ballBounceBuffer.loadFromFile("Sounds/BallBounce.ogg")) {
		std::cout << "BallBounce sound not loaded" << std::endl;
	}

	if (!blockHitBuffer.loadFromFile("Sounds/BlockHit.ogg")) {
		std::cout << "BlockHit sound not loaded" << std::endl;
	}

	if (!buttonClickBuffer.loadFromFile("Sounds/ButtonClick.ogg")) {
		std::cout << "ButtonClick sound not loaded" << std::endl;
	}

	if (!powerUpBuffer.loadFromFile("Sounds/PowerUpHit.ogg")) {
		std::cout << "PowerUpHit sound not loaded" << std::endl;
	}

	ballBounce.setBuffer(ballBounceBuffer);
	blockHit.setBuffer(blockHitBuffer);
	buttonClick.setBuffer(buttonClickBuffer);
	powerUpSound.setBuffer(powerUpBuffer);
	return true;
}

void App::Update()
{	
	if (!levelPaused) {
		// move the ball 
		Ball.move(xBallSpeed * deltaTime, yBallSpeed * deltaTime);

		//PowerUp Move
		if (increasePaddleSpawned)
		{
			increasePaddlePowerUp.move(sf::Vector2f(0, 500 * deltaTime));
		}

		if (increaseScoreSpawned)
		{
			increaseScorePowerUp.move(sf::Vector2f(0, 500 * deltaTime));
		}

		if (firePowerUpSpawned)
		{
			firePowerUp.move(sf::Vector2f(0, 500 * deltaTime));
		}

		if (increasePaddlePowerUp.getPosition().y >= 1200)
		{
			increasePaddleSpawned = false;
		}

		if (increaseScorePowerUp.getPosition().y >= 1200)
		{
			increaseScoreSpawned = false;
		}

		if (firePowerUp.getPosition().y >= 1200)
		{
			firePowerUpSpawned = false;
		}

		if (IncreasePaddleActivated)
		{
			if (clock_IncreasePaddle.getElapsedTime().asSeconds() >= 6.00f)
			{
				IncreasePaddleActivated = false;
				paddle.setSize(sf::Vector2f(paddleWidth, paddleHeight));
			}
	    }

		if (IncreaseScoreActivated) 
		{
			if (clock_IncreaseScore.getElapsedTime().asSeconds() >= 4.00f)
			{
				IncreaseScoreActivated = false;
			}
		}

		if (FirePowerUpActivated) 
		{
			if (clock_FirePowerUp.getElapsedTime().asSeconds() >= 5.00f)
			{
				FirePowerUpActivated = false;
				Ball.setTexture(&ballTexture);
			}
		}

		// move Paddle left, frame rate independent
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			if (paddle.getPosition().x >= 0)
			{
				paddle.move(-paddlespeed * deltaTime, 0);
			}
		}

		// move Paddle right, frame rate independent
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			if (paddle.getPosition().x <= (window.getSize().x - paddle.getSize().x))
			{
				paddle.move(paddlespeed * deltaTime, 0);
			}
		}

		// left border collision detection
		if (Ball.getPosition().x <= 0)
		{
			xBallSpeed = -xBallSpeed;
			ballBounce.play();
		}

		// right border collision detection
		if (Ball.getPosition().x >= window.getSize().x - 2 * radius)
		{
			xBallSpeed = -xBallSpeed;
			ballBounce.play();
		}

		// top border collision detection
		if (Ball.getPosition().y <= 0)
		{
			yBallSpeed = -yBallSpeed;
			ballBounce.play();
		}

		// bottom border collision detection
		if (Ball.getPosition().y >= window.getSize().y - 2 * radius)
		{
			IncreasePaddleActivated = false;
			IncreaseScoreActivated = false;
			FirePowerUpActivated = false;

			increasePaddleSpawned = false;
			increaseScoreSpawned = false;
			firePowerUpSpawned = false;

			paddle.setSize(sf::Vector2f(paddleWidth, paddleHeight));
			Ball.setTexture(&ballTexture);
			//Reset All the PowerUp Values

			if (livesLeft <= 1) 
			{
				// Game Over 
				gameOver = true;
				levelPaused = true;
				customLevel = false;		

				gameWonScoreText.setString(std::to_string(score));
				yBallSpeed = -yBallSpeed;
			}
			else
			{
				livesLeft--;
				yBallSpeed = -yBallSpeed;
				Ball.setRadius(radius);
				Ball.setPosition((window.getSize().x / 2) - radius, (window.getSize().y / 2) + 200);
			}
		}

		// detect collision with collidable brick 
		// i.e. if brick has not been hit
		if (!levelPaused) {
			for (int row = 0; row < ROWS; ++row)
			{
				for (int col = 0; col < COLS; ++col)
				{
						if (Ball.getGlobalBounds().intersects(b[row][col].getGlobalBounds()) && collidable[row][col] == true)
						{
							// destroy the brick
							collidable[row][col] = false;
							smokeAnimation[row][col] = true;
							GenerateRandomPowerUp(b[row][col].getPosition().x, b[row][col].getPosition().y);
							score++;
							atext.setString(std::to_string(score));
							noOfBricks--;
							blockHit.play();
							if (noOfBricks <= 0)
							{
								//Game Won
								gameWon = true;
								levelPaused = true;
								customLevel = false;
								gameWonScoreText.setString(std::to_string(score));
								yBallSpeed = -yBallSpeed;
							}
							if (!FirePowerUpActivated) {

								// left or right border
								if (
									Ball.getPosition().x > b[row][col].getPosition().x + brickLength - pad ||
									Ball.getPosition().x + 2 * radius < b[row][col].getPosition().x + pad
									)
								{
									// reset position
									// reverse x speed
									xBallSpeed = -xBallSpeed;
								}

								// top or bottom border
								if (
									Ball.getPosition().y + 2 * radius < b[row][col].getPosition().y + pad ||
									Ball.getPosition().y > b[row][col].getPosition().y + brickHeight - pad
									)
								{
									// reset position
									// reverse y speed
									yBallSpeed = -yBallSpeed;
								}
							}
						}

						//Play Smoke Animations
						if (smokeAnimation[row][col])
						{
							if (smokeAnimRect[row][col].left > 0)
							{
								if (newClock.getElapsedTime().asSeconds() > 0.03f)
								{
									smokeAnimRect[row][col].left -= 600;
									smokeAnimSprite[row][col].setTextureRect(smokeAnimRect[row][col]);
									newClock.restart();
								}
							}
							else
							{
								smokeAnimation[row][col] = false;
								smokeAnimRect[row][col].left = 5400;
							}
						}
				}
			}
		}

		//Detect Paddle Collision
		if (Ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
		{
			int sign = 2 * (rand() % 2) - 1;

			xBallSpeed = sign * (rand() % 100 + 700);
			yBallSpeed = -yBallSpeed;
			ballBounce.play();
		}

		//Collision Between Paddle & Increase Paddle PowerUp
		if (paddle.getGlobalBounds().intersects(increasePaddlePowerUp.getGlobalBounds()))
		{
			if (!IncreasePaddleActivated) 
			{
				clock_IncreasePaddle.restart();
				StartIncreasePaddlePowerUp();
				//Play PowerUp Sound 
				powerUpSound.play();
			}
		}

		//Collision Between Paddle & Increase Score PowerUp
		if (paddle.getGlobalBounds().intersects(increaseScorePowerUp.getGlobalBounds()))
		{
			if (!IncreaseScoreActivated) 
			{
				clock_IncreaseScore.restart();
				StartIncreaseScorePowerUp();
				//Play PowerUp Sound
				powerUpSound.play();
			}
		}

		//Collision Between Paddle & Fire PowerUp
		if (paddle.getGlobalBounds().intersects(firePowerUp.getGlobalBounds()))
		{
			if (!FirePowerUpActivated) 
			{
				clock_FirePowerUp.restart();
				StartFirePowerUp();
				//Play PowerUp Sound
				powerUpSound.play();
			}
		}
	}
}

void App::InitializeArrayOfBricks() 
{
	noOfBricks = ROWS * COLS;
	// declare
	b = new sf::RectangleShape * [ROWS];

	// dynamically allocate memory for arrays of integers
	for (int i = 0; i < ROWS; ++i) 
	{
		b[i] = new sf::RectangleShape[COLS];
	}

	// initialise the bricks & collidable condition of bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			b[row][col].setSize(sf::Vector2f(brickLength, brickHeight));
			b[row][col].setPosition(edgeGap + col * (brickLength + gap), 20 + row * (brickHeight + gap));
			b[row][col].setTexture(&blueBlockTexture);
			collidable[row][col] = true;
			smokeAnimSprite[row][col].setPosition((b[row][col].getPosition().x) - 25, (b[row][col].getPosition().y) - 70);
			smokeAnimSprite[row][col].setTexture(smoke_Texture);
			smokeAnimSprite[row][col].setTextureRect(smokeAnimRect[row][col]);
			smokeAnimSprite[row][col].setScale(0.3, 0.3);
			smokeAnimation[row][col] = false;
		}
	}
}

void App::InitializeCustomArrayOfBricks()
{
	// declare
	b = new sf::RectangleShape * [ROWS];

	// dynamically allocate memory for arrays of  

	for (int i = 0; i < ROWS; ++i)
	{
		b[i] = new sf::RectangleShape[COLS];
	}

	// initialise the bricks & collidable condition of bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			b[row][col].setSize(sf::Vector2f(brickLength, brickHeight));
			b[row][col].setPosition(edgeGap + col * (brickLength + gap), 20 + row * (brickHeight + gap));
	        b[row][col].setTexture(&redBlockTexture);
			blockColor[row][col] = Red;
			smokeAnimSprite[row][col].setPosition((b[row][col].getPosition().x) - 25, (b[row][col].getPosition().y) - 70);
			smokeAnimSprite[row][col].setTexture(smoke_Texture);
			smokeAnimSprite[row][col].setTextureRect(smokeAnimRect[row][col]);
			smokeAnimSprite[row][col].setScale(0.3, 0.3);
			smokeAnimation[row][col] = false;
		}
	}
}

void App::StartLevel()
{
	//Calculation of No of activated bricks
	int deactivatedBricks = 0;
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			//Smoke Animation
			smokeAnimRect[row][col].left = 5400;
			smokeAnimRect[row][col].top = 0;
			smokeAnimRect[row][col].height = 600;
			smokeAnimRect[row][col].width = 600;

			if (collidable[row][col] == false)
			{
				deactivatedBricks++;
			}
		}
	}

	noOfBricks = (ROWS * COLS) - deactivatedBricks;

	//Ball
	livesLeft = 3;
	Ball.setRadius(radius);
	Ball.setPosition((window.getSize().x / 2) - radius, (window.getSize().y / 2) + 350);

	//Update Text
	score = 0;
	atext.setString(std::to_string(score));

	levelPaused = false;
	gameOver = false;
	gameWon = false;
}

void App::ResetAllMenuButtons() 
{
	//Menu Button Reset Values
	enablerMenuSelected = false;
	redMenuSelected = false;
	blueMenuSelected = false;
	purpleMenuSelected = false;
	greenMenuSelected = false;

	float menuBtnLength = 100;
	float menuBtnHeight = 100;
	enablerMenuButton.setSize(sf::Vector2f(menuBtnLength, menuBtnLength));
	enablerMenuButton.setPosition((window.getSize().x / 2) - (menuBtnLength / 2) - 400, (window.getSize().y / 2) - (menuBtnLength / 2));
	enablerMenuButton.setTexture(&enablerMenuTexture);

	redMenuButton.setSize(sf::Vector2f(menuBtnLength, menuBtnHeight));
	redMenuButton.setPosition((window.getSize().x / 2) - (menuBtnLength / 2) - 200, (window.getSize().y / 2) - (menuBtnHeight / 2));
	redMenuButton.setTexture(&redMenuTexture);

	blueMenuButton.setSize(sf::Vector2f(menuBtnLength, menuBtnHeight));
	blueMenuButton.setPosition((window.getSize().x / 2) - (menuBtnLength / 2), (window.getSize().y / 2) - (menuBtnHeight / 2));
	blueMenuButton.setTexture(&blueMenuTexture);

	purpleMenuButton.setSize(sf::Vector2f(menuBtnLength, menuBtnHeight));
	purpleMenuButton.setPosition((window.getSize().x / 2) - (menuBtnLength / 2) + 200, (window.getSize().y / 2) - (menuBtnHeight / 2));
	purpleMenuButton.setTexture(&purpleMenuTexture);

	greenMenuButton.setSize(sf::Vector2f(menuBtnLength, menuBtnHeight));
	greenMenuButton.setPosition((window.getSize().x / 2) - (menuBtnLength / 2) + 400, (window.getSize().y / 2) - (menuBtnHeight / 2));
	greenMenuButton.setTexture(&greenMenuTexture);
}

void App::GenerateRandomPowerUp(float x, float y)
{
	int ran;
	ran = rand() % 6;
	//Generate Random Number Between 0 & 5
	float powerUpRadius = 0.13;

	if (ran == 0)
	{
		if (!increasePaddleSpawned) {
			increasePaddleSpawned = true;
			increasePaddlePowerUp.setTexture(increasePaddlePowerUpTexture);
			increasePaddlePowerUp.setScale(powerUpRadius, powerUpRadius);
			increasePaddlePowerUp.setPosition(x, y);
		}
	}
	else if (ran == 1)
	{
		if (!increaseScoreSpawned) {
			increaseScoreSpawned = true;
			increaseScorePowerUp.setTexture(increaseScorePowerUpTexture);
			increaseScorePowerUp.setScale(0.11, 0.11);
			increaseScorePowerUp.setPosition(x, y);
		}
	}
	else if (ran == 2)
	{
		if (!firePowerUpSpawned) {
			firePowerUpSpawned = true;
			firePowerUp.setTexture(firePowerUpTexture);
			firePowerUp.setScale(powerUpRadius, powerUpRadius);
			firePowerUp.setPosition(x, y);
		}
	}
}

void App::StartIncreasePaddlePowerUp() 
{
	//Increase Paddle PowerUp Activated
	increasePaddlePowerUp.setPosition(0, 0);
	increasePaddleSpawned = false;
	IncreasePaddleActivated = true;
	paddle.setSize(sf::Vector2f(300, paddleHeight));
}

void App::StartIncreaseScorePowerUp()
{
	//Increase Score PowerUp Activated
	increaseScorePowerUp.setPosition(0, 0);
	increaseScoreSpawned = false;
	IncreaseScoreActivated = true;
	score += 3;
	atext.setString(std::to_string(score));
}

void App::StartFirePowerUp()
{
	//Fire PowerUp Activated
	firePowerUp.setPosition(0, 0);
	firePowerUpSpawned = false;
	FirePowerUpActivated = true;
	Ball.setTexture(&fireBallTexture);
}

void App::Draw()
{
	window.clear();
	window.setView(view);
	if (levelPaused)
	{
		if (!gameOver && !gameWon && !customLevel)
		{
			//Display Starting Main Menu	
			window.draw(bgSprite);
			window.draw(playButton);
			window.draw(playBtnText);
			window.draw(customLevelButton);
			window.draw(customLevelBtnText);
			window.draw(quitButton);
			window.draw(quitBtnText);
		}

		else if (customLevel) 
		{	
			//Display Customize Level Menu	
			window.draw(bgSprite);
			window.draw(customMenuButton);
			window.draw(customPlayButton);
			window.draw(customMenuBtnText);
			window.draw(customPlayBtnText);
			window.draw(enablerMenuButton);
			window.draw(redMenuButton);
			window.draw(blueMenuButton);
			window.draw(greenMenuButton);
			window.draw(purpleMenuButton);


			for (int row = 0; row < ROWS; ++row)
			{
				for (int col = 0; col < COLS; ++col)
				{
					if (collidable[row][col] == true)
					{
						window.draw(b[row][col]);
					}				
				}
			}
		}

		else if (gameOver)
		{
			//GameOver Menu
			window.draw(bgSprite);
			window.draw(menuButton);
			window.draw(menuBtnText);
			window.draw(gameOverText);
		}
		else if (gameWon)
		{
			//GameWon Menu
			window.draw(bgSprite);
			window.draw(menuButton);
			window.draw(menuBtnText);
			window.draw(gameWonText);
			window.draw(gameWonScoreText);
		}
	}
	else
	{
		if (!gameOver && !gameWon)
		{
			//Game Scene
			window.draw(bgSprite);
			window.draw(Ball);
			window.draw(paddle);
			window.draw(atext);
			if(increasePaddleSpawned)
			{
				window.draw(increasePaddlePowerUp);
			}

			if (increaseScoreSpawned)
			{
				window.draw(increaseScorePowerUp);
			}

			if (firePowerUpSpawned)
			{
				window.draw(firePowerUp);
			}

			//Managing Lives left
			if (livesLeft >= 3) {
				window.draw(lives1);
				window.draw(lives2);
				window.draw(lives3);
			}
			else if (livesLeft == 2)
			{
				window.draw(lives1);
				window.draw(lives2);
			}
			else
			{
				window.draw(lives1);
			}

			// Draw the bricks
			for (int row = 0; row < ROWS; ++row)
			{
				for (int col = 0; col < COLS; ++col)
				{
					if (collidable[row][col] == true)
					{
						window.draw(b[row][col]);
					}
				}
			}

			// Draw the Smoke Animations
			for (int row = 0; row < ROWS; ++row)
			{
				for (int col = 0; col < COLS; ++col)
				{
					if (smokeAnimation[row][col] == true)
					{
						window.draw(smokeAnimSprite[row][col]);
					}
				}
			}
		}
	}
	window.display();
}

void App::HandleEvents()
{
	// handle LMB
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) 
	{
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		if (playButton.getGlobalBounds().contains(sf::Vector2f(localPosition))) 
		{
			//On Play Button Click
			if (levelPaused && !gameOver && !gameWon && !customLevel) {
				bool click = false;
				if (!click)
				{
					click = true;
					buttonClick.play();
					InitializeArrayOfBricks();
					StartLevel();
					click = false;
				}
			}
		}

		if (customLevelButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Custom Level Button Click
			if (levelPaused && !gameOver && !gameWon && !customLevel) {
				//LoadCustomLevel;
				InitializeCustomArrayOfBricks();
				buttonClick.play();
				// open
				if (myfile.is_open())
				{
					// read from file
					for (int row = 0; row < ROWS; ++row)
					{
						for (int col = 0; col < COLS; ++col)
						{
							// only works with tab separated values
							myfile >> x[row][col];
							if (x[row][col] == 1)
							{
								collidable[row][col] = true;
							}
							else
							{
								collidable[row][col] = false;
							}
						}
					}
				}
				else
				{
					cout << "Unable to open file";
				}

				// open
				if (myColorFile.is_open())
				{
					for (int row = 0; row < ROWS; ++row)
					{
						for (int col = 0; col < COLS; ++col)
						{
							// only works with tab separated values
							myColorFile >> tempColor[row][col];

							if (tempColor[row][col] == Blue)
							{
								//Blue Block
								blockColor[row][col] = Blue;
								b[row][col].setTexture(&blueBlockTexture);
							}
							else if (tempColor[row][col] == Red)
							{
								//Red Block
								blockColor[row][col] = Red;
								b[row][col].setTexture(&redBlockTexture);
							}
							else if (tempColor[row][col] == Purple)
							{
								//Purple Block
								blockColor[row][col] = Purple;
								b[row][col].setTexture(&purpleBlockTexture);
							}
							else if (tempColor[row][col] == Green)
							{
								//Green Block
								blockColor[row][col] = Green;
								b[row][col].setTexture(&greenBlockTexture);
							}
							
						}
					}
				}
				else
				{
					cout << "Unable to open My Colors file";
				}
		
				customLevel = true;
				levelPaused = true;
				gameOver = false;
				gameWon = false;
			}
		}

		if (quitButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Quit Button Click
			if (levelPaused && !gameOver && !gameWon && !customLevel) {
				buttonClick.play();
				window.close();
			}
		}

		if (menuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Menu Button Click
			if (gameOver || gameWon && !customLevel) {
				buttonClick.play();
				gameOver = false;
				gameWon = false;
				levelPaused = true;
			}
		}

		if (customPlayButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Custom Play Button Click
			if (customLevel && levelPaused) 
			{	
				bool click = false;
				if (!click)
				{
					click = true;
					buttonClick.play();
					outfile.open("customLevel.txt", ios::out | ios::trunc);
					if (outfile.is_open())
					{
						// write to file
						for (int row = 0; row < ROWS; ++row) {
							for (int col = 0; col < COLS; ++col)
							{
								if (collidable[row][col] == true)
								{
									outfile << 1 << "\n";
								}
								else
								{
									outfile << 0 << "\n";
								}
							}
						}
					}
					else
					{
						cout << "Unable to open file";
					}

					outColorFile.open("customLevelColors.txt", ios::out | ios::trunc);
					if (outColorFile.is_open())
					{
						// write to file
						for (int row = 0; row < ROWS; ++row) {
							for (int col = 0; col < COLS; ++col)
							{
								if (blockColor[row][col] == Green)
								{
									outColorFile << 3 << "\n";
								}
								else if(blockColor[row][col] == Purple)
								{	
									outColorFile << 2 << "\n";
								}
								else if (blockColor[row][col] == Red)
								{
									outColorFile << 1 << "\n";
								}
								else if (blockColor[row][col] == Blue)
								{
									outColorFile << 0 << "\n";
								}
							}
						}
					}
					else
					{
						cout << "Unable to open file";
					}

					StartLevel();
					click = false;
				}
			}
		}

		if (customMenuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Custom Menu Button Click
			if (customLevel && levelPaused)
			{
				buttonClick.play();
				gameOver = false;
				gameWon = false;
				levelPaused = true;
				customLevel = false;
			}
		}

		if (customLevel && levelPaused)
		{
			for (int row = 0; row < ROWS; ++row)
			{
				for (int col = 0; col < COLS; ++col)
				{
					if (b[row][col].getGlobalBounds().contains(sf::Vector2f(localPosition)))
					{
						if (enablerMenuSelected) 
						{
							//On Customizable Brick Click
							if (collidable[row][col])
							{
								collidable[row][col] = false;
								noOfBricks--;
							}
							else
							{
								collidable[row][col] = true;
								noOfBricks++;
							}
						}
						else if(redMenuSelected)
						{
							blockColor[row][col] = Red;
							b[row][col].setTexture(&redBlockTexture);
						}
						else if (blueMenuSelected)
						{
							blockColor[row][col] = Blue;
							b[row][col].setTexture(&blueBlockTexture);
						}
						else if (purpleMenuSelected)
						{
							blockColor[row][col] = Purple;
							b[row][col].setTexture(&purpleBlockTexture);
						}
						else if (greenMenuSelected)
						{
							blockColor[row][col] = Green;
							b[row][col].setTexture(&greenBlockTexture);
						}
					}
				}
			}
		}

		if (enablerMenuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Enabler Menu Button Click
			if (customLevel && levelPaused)
			{
				if (enablerMenuSelected) 
				{
					ResetAllMenuButtons();
					enablerMenuSelected = false;
					enablerMenuButton.setSize(sf::Vector2f(100, 100));
					enablerMenuButton.setPosition((window.getSize().x / 2) - (100 / 2) - 400, (window.getSize().y / 2) - (100 / 2));
					enablerMenuButton.setTexture(&enablerMenuTexture);
				}
				else
				{
					ResetAllMenuButtons();
					enablerMenuSelected = true;
					enablerMenuButton.setSize(sf::Vector2f(80, 80));
					enablerMenuButton.setPosition((window.getSize().x / 2) - (80 / 2) - 400, (window.getSize().y / 2) - (80 / 2));
					enablerMenuButton.setTexture(&enablerMenuOnclickTexture);
				}
			}
		}

		if (redMenuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Red Menu Button Click
			if (customLevel && levelPaused)
			{
				if (redMenuSelected)
				{
					ResetAllMenuButtons();
					redMenuSelected = false;
					redMenuButton.setSize(sf::Vector2f(100, 100));
					redMenuButton.setPosition((window.getSize().x / 2) - (100 / 2) - 200, (window.getSize().y / 2) - (100 / 2));
					redMenuButton.setTexture(&redMenuTexture);
				}
				else
				{
					ResetAllMenuButtons();
					redMenuSelected = true;
					redMenuButton.setSize(sf::Vector2f(80, 80));
					redMenuButton.setPosition((window.getSize().x / 2) - (80 / 2) - 200, (window.getSize().y / 2) - (80 / 2));
					redMenuButton.setTexture(&redMenuOnclickTexture);
				}
			}
		}

		if (blueMenuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Red Menu Button Click
			if (customLevel && levelPaused)
			{
				if (blueMenuSelected)
				{
					ResetAllMenuButtons();
					blueMenuSelected = false;
					blueMenuButton.setSize(sf::Vector2f(100, 100));
					blueMenuButton.setPosition((window.getSize().x / 2) - (100 / 2), (window.getSize().y / 2) - (100 / 2));
					blueMenuButton.setTexture(&blueMenuTexture);
				}
				else
				{
					ResetAllMenuButtons();
					blueMenuSelected = true;
					blueMenuButton.setSize(sf::Vector2f(80, 80));
					blueMenuButton.setPosition((window.getSize().x / 2) - (80 / 2), (window.getSize().y / 2) - (80 / 2));
					blueMenuButton.setTexture(&blueMenuOnclickTexture);
				}
			}
		}

		if (purpleMenuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Red Menu Button Click
			if (customLevel && levelPaused)
			{
				if (purpleMenuSelected)
				{
					ResetAllMenuButtons();
					purpleMenuSelected = false;
					purpleMenuButton.setSize(sf::Vector2f(100, 100));
					purpleMenuButton.setPosition((window.getSize().x / 2) - (100 / 2) + 200, (window.getSize().y / 2) - (100 / 2));
					purpleMenuButton.setTexture(&purpleMenuTexture);
				}
				else
				{
					ResetAllMenuButtons();
					purpleMenuSelected = true;
					purpleMenuButton.setSize(sf::Vector2f(80, 80));
					purpleMenuButton.setPosition((window.getSize().x / 2) - (80 / 2) + 200, (window.getSize().y / 2) - (80 / 2));
					purpleMenuButton.setTexture(&purpleMenuOnclickTexture);
				}
			}
		}

		if (greenMenuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			//On Red Menu Button Click
			if (customLevel && levelPaused)
			{
				if (greenMenuSelected)
				{
					ResetAllMenuButtons();
					greenMenuSelected = false;
					greenMenuButton.setSize(sf::Vector2f(100, 100));
					greenMenuButton.setPosition((window.getSize().x / 2) - (100 / 2) + 400, (window.getSize().y / 2) - (100 / 2));
					greenMenuButton.setTexture(&greenMenuTexture);
				}
				else
				{
					ResetAllMenuButtons();
					greenMenuSelected = true;
					greenMenuButton.setSize(sf::Vector2f(80, 80));
					greenMenuButton.setPosition((window.getSize().x / 2) - (80 / 2) + 400, (window.getSize().y / 2) - (80 / 2));
					greenMenuButton.setTexture(&greenMenuOnclickTexture);
				}
			}
		}
	}

	if (event.type == sf::Event::Closed)
	{
		window.close();
	}
}

void App::Run()
{
	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			HandleEvents();
		}
		Update();
		Draw();
	}
}