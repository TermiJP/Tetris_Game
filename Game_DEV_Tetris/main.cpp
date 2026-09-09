#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 320, 480 }), "SFML window");

    sf::Texture t;
    t.loadFromFile("images/tiles.png");

    sf::Sprite sprite(t);

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