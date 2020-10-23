#include "App.h"

// constructor
App::App(const char* title, int screenWidth, int screenHeight, int screenBpp)
{
	window.create(sf::VideoMode(screenWidth, screenHeight, screenBpp), title);
	window.setFramerateLimit(0);
	view = window.getDefaultView();
}

// destructor
App::~App() {}
bool App::Init()
{
	//Circle
	radius = 15;
	Ball.setRadius(radius);

	// random speed
	xBallSpeed = rand() % 100 + 500;
	yBallSpeed = rand() % 100 + 500;

	//Ball.setPosition((window.getSize().x / 2) - radius, (window.getSize().y / 2) - radius);

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

	// initialise the bricks & collidable condition of bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			Bricks[row][col].setSize(sf::Vector2f(brickLength, brickHeight));
			Bricks[row][col].setPosition(edgeGap + col * (brickLength + gap), 20 + row * (brickHeight + gap));
			collidable[row][col] = true;
		}
	}

	// that an object may move after a collision is detected
	pad = 20;
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
		yBallSpeed = -yBallSpeed;
	}

	// detect collision with collidable brick 
	// i.e. if brick has not been hit
	for (int row = 0; row < ROWS; ++row) 
	{
		for (int col = 0; col < COLS; ++col)
		{
			if (Ball.getGlobalBounds().intersects(Bricks[row][col].getGlobalBounds()) && collidable[row][col] == true)
			{
				// destroy the brick
				collidable[row][col] = false;

				// left or right border
				if (
					Ball.getPosition().x > Bricks[row][col].getPosition().x + brickLength - pad ||
					Ball.getPosition().x + 2 * radius < Bricks[row][col].getPosition().x + pad
					)
				{
					// reset position
					// reverse x speed
					xBallSpeed = -xBallSpeed;
				}

				// top or bottom border
				if (
					Ball.getPosition().y + 2 * radius < Bricks[row][col].getPosition().y + pad ||
					Ball.getPosition().y > Bricks[row][col].getPosition().y + brickHeight - pad
					)
				{
					// reset position
					// reverse y speed
					yBallSpeed = -yBallSpeed;
				}
			}
		}
		//Detect Paddle Collision
		if (Ball.getGlobalBounds().intersects(paddle.getGlobalBounds()))
		{
			xBallSpeed = (rand() % 500 + (-200));
			yBallSpeed = -yBallSpeed;
		}
	}
}

void App::Draw()
{
	window.clear();
	window.setView(view);
	window.draw(Ball);
	window.draw(paddle);	
	// draw the bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			if (collidable[row][col] == true) 
			{
				window.draw(Bricks[row][col]);
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
		deltaTime = clock.restart().asSeconds();
		while (window.pollEvent(event))
		{
			HandleEvents();
		}
		Update();
		Draw();
	}
}