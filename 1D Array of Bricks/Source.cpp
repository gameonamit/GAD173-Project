#include <SFML/Graphics.hpp>

int main()
{
	sf::RenderWindow Window(sf::VideoMode(640, 480), "SFML works!");

	const int N = 5;
	float Length = 100;

	float separation = 20;
	float xPadding = (Window.getSize().x - N * Length - (N - 1) * separation) / 2;

	// check 2d+N*Length+(N-1)*separation = WindowSize

	// declare an array of bricks
	sf::RectangleShape Bricks[N];

	// initialise the bricks
	for (int i = 0; i < N; ++i)
	{
		Bricks[i].setSize(sf::Vector2f(Length, 30));
		Bricks[i].setPosition(xPadding + i * (Length + separation), 50);
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
		for(int i = 0; i < N; ++i)
		{
			Window.draw(Bricks[i]);
		}
	    Window.display();;
	}

	return 0;
}
