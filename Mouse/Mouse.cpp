#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Audio.hpp>

using namespace std;


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Hello SFML World!");
	sf::RectangleShape button(sf::Vector2f(100.0f, 50.0f));
	button.setPosition(300, 200);
	bool collidible = true;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// handle LMB
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				sf::Vector2i localPosition = sf::Mouse::getPosition(window);
				if (button.getGlobalBounds().contains(sf::Vector2f(localPosition))) {
					//cout << "Hello World!" << endl;
					collidible = !collidible;
			
				}
			}
		}
		window.clear();
		if (collidible) 
		{
			window.draw(button);
		}
		window.display();
	}
	return EXIT_SUCCESS;
}