#include <SFML/Graphics.hpp>
#include <iostream>


int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hello SFML World!");

	sf::Texture texture;
	if (!texture.loadFromFile("SmokeAnimation.png"))
	{
		std::cout << "Unable to load image" << std::endl;
	}

	sf::IntRect rect(5400, 0, 600, 600);
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(rect);
	sprite.scale(0.4, 0.4);
	sprite.setPosition(800, 300);


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		if (clock.getElapsedTime().asSeconds() > 0.05f) {
			rect.left -= 600;
			sprite.setTextureRect(rect);
			clock.restart();
		}

		window.clear();
		window.draw(sprite);
		window.display();
	}
	return EXIT_SUCCESS;
}

// TASK: play only the first three sprites 
// in the proper order: 1, 2, 3, 2, 1, …

// TASK: move the sprite with user input (WASD)
// and play the appropriate animations

// TASK: transcribe into framework

