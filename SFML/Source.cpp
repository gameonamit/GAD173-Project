#include <SFML/Graphics.hpp>
int main()
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Hello SFML World!");
	sf::CircleShape circle(20.0f);
	circle.setPosition(640, 650);
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

		}
		window.clear();
		window.draw(circle);
		window.display();
	}
	return EXIT_SUCCESS;
}