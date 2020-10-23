#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow Window(sf::VideoMode(640, 480), "SFML works!");

	const int ROWS = 3;
	const int COLS = 5;
	float length = 30;
	float height = 30;

	float gap = 10;
	float edgeGap = (Window.getSize().x - COLS * length - (COLS - 1) * gap) / 2;

	// check 2d+N*Length+(N-1)*separation = WindowSize

	// declare an array of bricks
	sf::RectangleShape Bricks[ROWS][COLS];

	// initialise the bricks
	for (int row = 0; row < ROWS; ++row) {
		for (int col = 0; col < COLS; ++col)
		{
			Bricks[row][col].setSize(sf::Vector2f(length, height));
			Bricks[row][col].setPosition(edgeGap + col * (length + gap), 20 + row * (height + gap));
		}
	}

	while (Window.isOpen())
	{
		sf::Event event;
		while (Window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Window.close();
		}

		Window.clear();

		// draw the bricks
		for (int row = 0; row < ROWS; ++row) {
			for (int col = 0; col < COLS; ++col)
			{
				//Bricks[row][col].setSize(sf::Vector2f(length, height));
				//Bricks[row][col].setPosition(edgeGap + col * (length + gap), edgeGap + row * (height + gap));
				Window.draw(Bricks[row][col]);
			}
		}
		Window.display();
	}

	return 0;
}
