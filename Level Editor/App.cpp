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
	// open
	myfile.open("customLevel.txt", ios::out | ios::in);
	//outfile.open("customLevel.txt");
}

// destructor
App::~App() 
{
	myfile.close();
	//infile.close();
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
	livesLeft = 3;
	noOfBricks = ROWS * COLS;

	if (!font.loadFromFile("Fonts/myfont.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	if (!ballBounceBuffer.loadFromFile("Sounds/BallBounce.ogg")) {
		std::cout << "sound not loaded" << std::endl;
	}

	if (!blockHitBuffer.loadFromFile("Sounds/BlockHit.ogg")) {
		std::cout << "sound not loaded" << std::endl;
	}

	if (!buttonClickBuffer.loadFromFile("Sounds/ButtonClick.ogg")) {
		std::cout << "sound not loaded" << std::endl;
	}

	ballBounce.setBuffer(ballBounceBuffer);
	blockHit.setBuffer(blockHitBuffer);
	buttonClick.setBuffer(buttonClickBuffer);

	
	if (!bgTexture.loadFromFile("Sprites/galaxy.jpg"))
	{
		std::cout << "BG not loaded" << std::endl;
	}

	if (!blockTexture.loadFromFile("Sprites/block.png"))
	{
		std::cout << "BG not loaded" << std::endl;
	}

	if (!paddleTexture.loadFromFile("Sprites/paddle.png"))
	{
		std::cout << "BG not loaded" << std::endl;
	}

	if (!ballTexture.loadFromFile("Sprites/ball.png"))
	{
		std::cout << "BG not loaded" << std::endl;
	}
	if (!buttonCoverTexture.loadFromFile("Sprites/buttonCover.png"))
	{
		std::cout << "BG not loaded" << std::endl;
	}
	


	int x[COLS][ROWS];
	
	buttonLength = 700;
	buttonHeight = 150;
	int buttonGap = 200;
	int topGap = 140;

	//Play Button
	playButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	playButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight);
	playButton.setTexture(&buttonCoverTexture);

	
	playBtnText.setFont(font);
	playBtnText.setCharacterSize(80);
	playBtnText.setStyle(sf::Text::Regular);
	playBtnText.setFillColor(sf::Color::White);
	playBtnText.setString("Play");
	playBtnText.setPosition((window.getSize().x / 2) - (playBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + 20);

	//Custom Level Button
	customLevelButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	customLevelButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight + buttonGap);
	customLevelButton.setTexture(&buttonCoverTexture);


	customLevelBtnText.setFont(font);
	customLevelBtnText.setCharacterSize(80);
	customLevelBtnText.setStyle(sf::Text::Regular);
	customLevelBtnText.setFillColor(sf::Color::White);
	customLevelBtnText.setString("Custom Level");
	customLevelBtnText.setPosition((window.getSize().x / 2) - (customLevelBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + buttonGap + 20);

	//Quit Button
	quitButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	quitButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight + 2 * buttonGap);
	quitButton.setTexture(&buttonCoverTexture);

	quitBtnText.setFont(font);
	quitBtnText.setCharacterSize(80);
	quitBtnText.setStyle(sf::Text::Regular);
	quitBtnText.setFillColor(sf::Color::White);
	quitBtnText.setString("Quit");
	quitBtnText.setPosition((window.getSize().x / 2) - (quitBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + 2 * buttonGap + 20);

	//Menu Button
	menuButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	menuButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), (window.getSize().y / 2) + 150);
	menuButton.setTexture(&buttonCoverTexture);

	menuBtnText.setFont(font);
	menuBtnText.setCharacterSize(80);
	menuBtnText.setStyle(sf::Text::Regular);
	menuBtnText.setFillColor(sf::Color::White);
	menuBtnText.setString("Menu");
	menuBtnText.setPosition((window.getSize().x / 2) - (menuBtnText.getGlobalBounds().width / 2), (window.getSize().y / 2) + 150 + 20) ;

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
	gameWonScoreText.setCharacterSize(80);
	gameWonScoreText.setStyle(sf::Text::Regular);
	gameWonScoreText.setFillColor(sf::Color::Green);
	gameWonScoreText.setString(std::to_string(score));
	gameWonScoreText.setPosition((window.getSize().x / 2) - (gameWonScoreText.getGlobalBounds().width / 2), (window.getSize().y / 2) - 90);

	//customMenuButton Button
	customMenuButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	customMenuButton.setPosition((window.getSize().x / 2) - (customMenuButton.getGlobalBounds().width / 2) + 400, (window.getSize().y / 2) - (customMenuButton.getGlobalBounds().height / 2) + 300);
	customMenuButton.setTexture(&buttonCoverTexture);

	customMenuBtnText.setFont(font);
	customMenuBtnText.setCharacterSize(80);
	customMenuBtnText.setStyle(sf::Text::Regular);
	customMenuBtnText.setFillColor(sf::Color::White);
	customMenuBtnText.setString("Menu");
	customMenuBtnText.setPosition((window.getSize().x / 2) - (customMenuBtnText.getGlobalBounds().width / 2) + 400, (window.getSize().y / 2) - (customMenuBtnText.getGlobalBounds().height / 2) + 300 - 30);

	//customPlayBtnText Button
	customPlayButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	customPlayButton.setPosition((window.getSize().x / 2) - (customPlayButton.getGlobalBounds().width / 2) - 400, (window.getSize().y / 2) - (customPlayButton.getGlobalBounds().height / 2) + 300);
	customPlayButton.setTexture(&buttonCoverTexture);

	customPlayBtnText.setFont(font);
	customPlayBtnText.setCharacterSize(80);
	customPlayBtnText.setStyle(sf::Text::Regular);
	customPlayBtnText.setFillColor(sf::Color::White);
	customPlayBtnText.setString("Play");
	customPlayBtnText.setPosition((window.getSize().x / 2) - (customPlayBtnText.getGlobalBounds().width / 2) - 400, (window.getSize().y / 2) - (customPlayBtnText.getGlobalBounds().height / 2) + 300 - 20);

	//Circle
	radius = 15;
	Ball.setRadius(radius);
	Ball.setPosition((window.getSize().x / 2) - radius, (window.getSize().y / 2) + 350);
	Ball.setTexture(&ballTexture);

	int sign = 2 * (rand() % 2) - 1;
	// random speed
	xBallSpeed = sign * (rand() % 100 + 500);
	yBallSpeed = -(rand() % 100 + 500);

	//set up text properties
	score = 0;
	atext.setFont(font);
	atext.setCharacterSize( 80 );
	atext.setStyle(sf::Text::Bold);
	atext.setFillColor(sf::Color::Green);
	atext.setPosition(50, 30);

	//Paddle
	paddleWidth = 200;
	paddleHeight = 30;
	paddlespeed = 1000;

	paddle.setSize(sf::Vector2f(paddleWidth, paddleHeight));
	paddle.setPosition(window.getSize().x / 2 - paddleWidth / 2, 0.95f * window.getSize().y - 60);
	paddle.setTexture(&paddleTexture);

	//Brick specifications
	brickLength = 150;
	brickHeight = 50;

	//Brick Array
	gap = 10;
	edgeGap = (window.getSize().x - COLS * brickLength - (COLS - 1) * gap) / 2;

	// that an object may move after a collision is detected
	pad = 20;

	lives1.setTexture(ballTexture);
	lives1.setScale((Ball.getLocalBounds().width) / lives1.getLocalBounds().width, (Ball.getLocalBounds().width) / lives1.getLocalBounds().height);
	lives1.setPosition(window.getSize().x - 80, 30);

	lives2.setTexture(ballTexture);
	lives2.setScale((Ball.getLocalBounds().width) / lives2.getLocalBounds().width, (Ball.getLocalBounds().width) / lives2.getLocalBounds().height);
	lives2.setPosition(window.getSize().x - 140, 30);

	lives3.setTexture(ballTexture);
	lives3.setScale((Ball.getLocalBounds().width) / lives3.getLocalBounds().width, (Ball.getLocalBounds().width) / lives3.getLocalBounds().height);
	lives3.setPosition(window.getSize().x - 200, 30);

	bgSprite.setTexture(bgTexture);
	bgSprite.setScale((window.getSize().x) / bgSprite.getLocalBounds().width, (window.getSize().y) / bgSprite.getLocalBounds().height);

	return true;
}

void App::Update()
{	
	if (!levelPaused) {
		// move the ball 
		Ball.move(xBallSpeed * deltaTime, yBallSpeed * deltaTime);

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
			b[row][col].setTexture(&blockTexture);
			collidable[row][col] = true;
		}
	}
}

void App::InitializeCustomArrayOfBricks()
{
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
			b[row][col].setTexture(&blockTexture);
		}
	}
}


void App::StartLevel()
{
	int deactivatedBricks = 0;
	// initialise the bricks & collidable condition of bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			if (collidable[row][col] == false)
			{
				deactivatedBricks++;
			}
		}
	}
	noOfBricks = (ROWS * COLS) - deactivatedBricks;

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

void App::Draw()
{
	window.clear();
	window.setView(view);

	if (levelPaused)
	{
		if (!gameOver && !gameWon && !customLevel)
		{
			//Display Menu	
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
			window.draw(bgSprite);
			window.draw(customMenuButton);
			window.draw(customPlayButton);
			window.draw(customMenuBtnText);
			window.draw(customPlayBtnText);

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
			window.draw(bgSprite);
			window.draw(menuButton);
			window.draw(menuBtnText);
			window.draw(gameOverText);
		}
		else if (gameWon)
		{
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
			//Start a Game
			window.draw(bgSprite);
			window.draw(Ball);
			window.draw(paddle);
			window.draw(atext);

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

			// draw the bricks
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
	}
	window.display();
}

void App::HandleEvents()
{
	// handle LMB
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		sf::Vector2i localPosition = sf::Mouse::getPosition(window);
		if (playButton.getGlobalBounds().contains(sf::Vector2f(localPosition))) 
		{
			if (levelPaused && !gameOver && !gameWon && !customLevel) {
				bool click = false;
				if (!click)
				{
					click = true;
					buttonClick.play();
					cout << "Play Button Click" << endl;
					InitializeArrayOfBricks();
					StartLevel();
					click = false;
				}
			}
		}

		if (customLevelButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			if (levelPaused && !gameOver && !gameWon && !customLevel) {
				cout << "Custom Level Btn Click" << endl;
				//LoadCustomLevel();
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
							cout << x[row][col] << endl;
						}
					}
				}
				else
				{
					cout << "Unable to open file";
				}
				customLevel = true;
				levelPaused = true;
				gameOver = false;
				gameWon = false;
			}
		}

		if (quitButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			if (levelPaused && !gameOver && !gameWon && !customLevel) {
				cout << "Quit Btn Click" << endl;
				buttonClick.play();
				window.close();
			}
		}

		if (menuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			if (gameOver || gameWon && !customLevel) {
				cout << "Menu Btn Click" << endl;
				buttonClick.play();
				gameOver = false;
				gameWon = false;
				levelPaused = true;
			}
		}

		if (customPlayButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			if (customLevel && levelPaused) 
			{	
				bool click = false;
				if (!click)
				{
					click = true;
					cout << "Play Button Click" << endl;
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
					StartLevel();
					click = false;
				}
			}
		}



		if (customMenuButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			if (customLevel && levelPaused)
			{
				cout << "Menu Btn Click" << endl;
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
						if (collidable[row][col])
						{
							cout << "Brick Btn Click" << endl;
							collidable[row][col] = false;
							noOfBricks--;
						}
						else 
						{
							cout << "Brick Btn Click" << endl;
							collidable[row][col] = true;
							noOfBricks++;
						}
					}
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