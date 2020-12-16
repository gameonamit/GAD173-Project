#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

int main()
{
	sf::RenderWindow window(sf::VideoMode(1920, 1080), "Hello SFML World!");

	// declaration and initialisation
	sf::CircleShape circle(100.0f);

	//sf::RectangleShape brick(sf::Vector2f(200, 100));

	//brick.setPosition(1000, 500);

	// load a background image
	sf::Image backgroundImage;
	if (!backgroundImage.loadFromFile("galaxy.jpg"))
	{
		cout << "Unable to load image" << endl;
	}

	// create a texture from the image
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromImage(backgroundImage);

	// create a sprite from the texture
	sf::Sprite backgroundSprite;
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(float(window.getSize().x) / backgroundTexture.getSize().x, float(window.getSize().y) / backgroundTexture.getSize().y);

	// load a texture
	sf::Texture texture;
	if (!texture.loadFromFile("brick.jpg"))
	{
		cout << "Unable to load texture" << endl;
	}

	// declare a sprite
	sf::Sprite sprite;
	sprite.setTexture(texture);
	sprite.setPosition(1000, 500);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		window.draw(backgroundSprite);
		window.draw(circle);
		//window.draw(brick);
		window.draw(sprite);
		window.display();
	}
	return EXIT_SUCCESS;
}