#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

int main()
{
    sf::Clock Clock;

    sf::RenderWindow Window(sf::VideoMode(640, 480), "SFML works!");

    float radius = 25;
    sf::CircleShape Ball(25.f);
    float xSpeed = 100;


    sf::RectangleShape Brick(sf::Vector2f(100, 50));
    Brick.setPosition(500, 0);

    // sound
    sf::SoundBuffer buffer;

    if (!buffer.loadFromFile("button.wav")) {
        std::cout << "sound not loaded\n";
        return -1;
    }

    sf::Sound sound3;
    sound3.setBuffer(buffer);


    while (Window.isOpen())
    {
        float deltaTime = Clock.restart().asSeconds();
        sf::Event event;
        while (Window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                Window.close();
            }

            // spacebar press
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                sound3.play();
            }
        }


        // collision detection
        if (Ball.getGlobalBounds().intersects(Brick.getGlobalBounds()))
        {
            sound3.play();

            // reset position


            // reverse speed
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