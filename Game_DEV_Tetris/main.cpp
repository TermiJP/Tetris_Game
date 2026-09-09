#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

const int M = 20;
const int N = 10;

int field[M][N] = { 0 };

struct Point
{int x, y;} a[4], b[4];

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

    int dx = 0; bool rotate = 0; int colorNum = 1;

    float timer = 0, delay = 0.3;

    sf::Clock clock;

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        while (const std::optional event = window.pollEvent())
        {

            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;


            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();

            if (event->is<sf::Event::KeyPressed>())
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                    if (keyPressed->code == sf::Keyboard::Key::Up) rotate = true;
                    else if (keyPressed->code == sf::Keyboard::Key::Left) dx = -1;
                    else if (keyPressed->code == sf::Keyboard::Key::Right) dx = 1;

            ///// Move /////
            for (int i = 0; i < 4;i++)  a[i].x += dx;

            ///// Rotate /////
            if (rotate) 
            {
                Point p = a[1]; //Center of rotation
                for (int i = 0;i < 4;i++) {
                    int x = a[i].y - p.y;
                    int y = a[i].x - p.x;
                    a[i].x = p.x - x;
                    a[i].y = p.y + y;
                }
            }
                    
        }

        ////// Tick /////
        if (timer > delay) {
            for (int i = 0;i < 4;i++) a[i].y += 1;
            timer = 0;
        }

        int n = 3;
        if(a[0].x==0)
        for (int i = 0; i < 4;i++) 
        {
            a[i].x = figures[n][i] % 2;
            a[i].y = figures[n][i] / 2;

        }

        dx = 0; rotate = 0;

        // Clear screen
        window.clear(sf::Color::White);

        for (int i = 0;i < 4;i++) 
        {
            sprite.setPosition({ a[i].x * 18.f, a[i].y * 18.f });
            window.draw(sprite);
        }
        
        window.display();
    }
}