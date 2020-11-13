#include "App.h"
#include <sfml/Graphics.hpp>
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
	myfile.open("example.txt");
	newfile.open("example.txt");
}

// destructor
App::~App() 
{
	myfile.close();
	newfile.close();

	//Memory Allocation
	for (int i = 0; i < ROWS; ++i) {
		delete[] b[i];
	}
	delete[] b;
}

bool App::Init()
{
	InitializeArrayOfBricks();

	if (!font.loadFromFile("Fonts/myfont.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}
	
	buttonLength = 700;
	buttonHeight = 150;
	int buttonGap = 200;
	int topGap = 140;
	levelPaused = true;

	//Play Button
	playButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	playButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight);

	
	playBtnText.setFont(font);
	playBtnText.setCharacterSize(100);
	playBtnText.setStyle(sf::Text::Regular);
	playBtnText.setFillColor(sf::Color::Red);
	playBtnText.setString("Play");
	playBtnText.setPosition((window.getSize().x / 2) - (playBtnText.getGlobalBounds().width / 2), topGap + buttonHeight);

	//Custom Level Button
	customLevelButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	customLevelButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight + buttonGap);


	customLevelBtnText.setFont(font);
	customLevelBtnText.setCharacterSize(100);
	customLevelBtnText.setStyle(sf::Text::Regular);
	customLevelBtnText.setFillColor(sf::Color::Red);
	customLevelBtnText.setString("Custom Level");
	customLevelBtnText.setPosition((window.getSize().x / 2) - (customLevelBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + buttonGap);

	//Quit Button
	quitButton.setSize(sf::Vector2f(buttonLength, buttonHeight));
	quitButton.setPosition((window.getSize().x / 2) - (buttonLength / 2), topGap + buttonHeight + 2 * buttonGap);


	quitBtnText.setFont(font);
	quitBtnText.setCharacterSize(100);
	quitBtnText.setStyle(sf::Text::Regular);
	quitBtnText.setFillColor(sf::Color::Red);
	quitBtnText.setString("Quit");
	quitBtnText.setPosition((window.getSize().x / 2) - (quitBtnText.getGlobalBounds().width / 2), topGap + buttonHeight + 2 * buttonGap);

	//Circle
	radius = 15;
	Ball.setRadius(radius);
	Ball.setPosition((window.getSize().x / 2) - radius, (window.getSize().y / 2) + 350);

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
	atext.setString(std::to_string(score));

	//Paddle
	paddleWidth = 200;
	paddleHeight = 30;
	paddlespeed = 1000;

	paddle.setSize(sf::Vector2f(paddleWidth, paddleHeight));
	paddle.setFillColor(sf::Color::Green);
	paddle.setPosition(window.getSize().x / 2 - paddleWidth / 2, 0.95f * window.getSize().y - 60);

	//Brick specifications
	brickLength = 150;
	brickHeight = 50;

	//Brick Array
	gap = 20;
	edgeGap = (window.getSize().x - COLS * brickLength - (COLS - 1) * gap) / 2;

	// that an object may move after a collision is detected
	pad = 20;

	/*for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			// write to file
			myfile << b[row][col].getPosition().x << "\t" << b[row][col].getPosition().y;
		}
	}

	int x[ROWS] = { };
	int y[COLS] = { };

	if(!newfile.eof())
	{
		for (int row = 0; row < ROWS; ++row) {
			for (int col = 0; col < COLS; ++col)
			{
				// only works with tab separated values
				newfile >> x[row] >> y[col];
				cout << x[row] << "\t" << y[col] << endl;
			}
		}
	}	
	else 
	{
		cout << "Unable to open file";
	}*/
	return true;
}

void App::Update()
{
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
	}

	// right border collision detection
	if (Ball.getPosition().x >= window.getSize().x - 2 * radius)
	{
		xBallSpeed = -xBallSpeed;
	}

	// top border collision detection
	if (Ball.getPosition().y <= 0)
	{
		yBallSpeed = -yBallSpeed;
	}

	// bottom border collision detection
	if (Ball.getPosition().y >= window.getSize().y - 2 * radius)
	{
		// Game Over // Game Over
		levelPaused = true;
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
        xBallSpeed = sign * (rand() % 100 + 500);
		yBallSpeed = -yBallSpeed;	
	}
}

void App::InitializeArrayOfBricks() 
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
			collidable[row][col] = true;
		}
	}
}

void App::StartLevel()
{
	levelPaused = false;
}

void App::Draw()
{
	window.clear();
	window.setView(view);
	
	if (levelPaused) {
		//Display Menu
		window.draw(playButton);
		window.draw(playBtnText);
		window.draw(customLevelButton);
		window.draw(customLevelBtnText);
		window.draw(quitButton);
		window.draw(quitBtnText);
	}
	else if (!levelPaused) 
	{
		//Start a Game
		window.draw(Ball);
		window.draw(paddle);
		window.draw(atext);
		// draw the bricks
		for (int row = 0; row < ROWS; ++row) {
			for (int col = 0; col < COLS; ++col)
			{
				if (collidable[row][col] == true)
				{
					window.draw(b[row][col]);
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
			bool click = false;
			if (!click) 
			{
				click = true;
				cout << "Play Button Click" << endl;	
				InitializeArrayOfBricks();
				StartLevel();
				click = false;
			}
		}

		if (customLevelButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			cout << "Custom Level Btn Click" << endl;
		}

		if (quitButton.getGlobalBounds().contains(sf::Vector2f(localPosition)))
		{
			window.close();
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