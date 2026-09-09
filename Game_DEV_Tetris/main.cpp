#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

const int M = 20;
const int N = 10;

int figures[7][4] =
{
    1,3,5,7, // I
    2,4,5,7, // Z
    3,5,4,6, // S
    3,5,4,7, // T
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 320, 480 }), "SFML window");

    sf::Texture t;
    t.loadFromFile("images/tiles.png");

    sf::Sprite sprite(t);
    sprite.setTextureRect(sf::IntRect({ 0, 0 }, { 18, 18 }));

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear screen
        window.clear(sf::Color::White);
        window.draw(sprite);
        window.display();
    }
}