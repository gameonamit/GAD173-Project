#include <SFML/Graphics.hpp>

int main()
{
    sf::Clock Clock;

    sf::RenderWindow Window(sf::VideoMode(640, 480), "SFML works!");

    float radius = 25;
    sf::CircleShape Ball(25.f);
    float xSpeed = 100;


    sf::RectangleShape Brick(sf::Vector2f(100, 50));
    Brick.setPosition(500, 0);


    while (Window.isOpen())
    {
        float deltaTime = Clock.restart().asSeconds();
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                Window.close();
        }


        // collision detection
        if (Ball.getGlobalBounds().intersects(Brick.getGlobalBounds()))
        {
            xSpeed = -xSpeed;
        }


        Ball.move(xSpeed * deltaTime, 0);


        Window.clear();
        Window.draw(Ball);
        Window.draw(Brick);
        Window.display();
    }

    return 0;
}