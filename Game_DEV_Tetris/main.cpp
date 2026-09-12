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
    1,3,5,7, // I             // 0 1
    2,4,5,7, // Z             // 2 3
    3,5,4,6, // S             // 4 5
    3,5,4,7, // T             // 6 7
    2,3,5,7, // L
    3,5,7,6, // J
    2,3,4,5, // O
};

bool check() 
{
    for (int i = 1;i < 4;i++)
        if (a[i].x<0 || a[i].x>N || a[i].y >= M) return 0;
        else if (field[a[i].y][a[i].x]) return 0;
    return 1;
}

int main()
{

    srand(time(0));

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({ 320, 480 }), "SFML window");

    //--------------------------TEXTURE--------------------------
    sf::Texture t;
    t.loadFromFile("images/tiles.png");

    //-----------------------TILE DE TEXTURA --------------------
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
            //---------------------------------TIMER--------------------------------
            float time = clock.getElapsedTime().asSeconds();
            clock.restart();
            timer += time;


            // Close window: exit
            if (event->is<sf::Event::Closed>())
                window.close();
             //-----------------------------KEYPRESSED------------------------------
            if (event->is<sf::Event::KeyPressed>())
                if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
                    if (keyPressed->code == sf::Keyboard::Key::Up) rotate = true;
                    else if (keyPressed->code == sf::Keyboard::Key::Left) dx = -1;
                    else if (keyPressed->code == sf::Keyboard::Key::Right) dx = 1;
            

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
                delay = 0.05f;
                    
        }

        ///// Move /////
        for (int i = 0; i < 4;i++)  a[i].x += dx;

        for (int i = 0;i < 4;i++) { b[i] = a[i]; a[i].x += dx; }

        if (!check()) for (int i = 0;i < 4;i++) a[i] = b[i];

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
            if (!check()) for (int i = 0;i < 4;i++) a[i] = b[i];
        }

        ////// Tick /////
        if (timer > delay) {
            for (int i = 0;i < 4;i++) { b[i] = a[i]; a[i].y += 1; }

            if (!check())
            {
                for (int i = 0;i < 4;i++) field[b[i].y][b[i].x] = colorNum;

                colorNum = 1 + rand() % 7;
                int n = rand() % 7;
                for (int i = 0;i < 4;i++) 
                {
                    a[i].x = figures[n][i] % 2;
                    a[i].y = figures[n][i] / 2;
                }
            }

            timer = 0;
        }


        dx = 0; rotate = 0; delay = 0.3f;

        ////// DRAW /////// 
        window.clear(sf::Color::White);

        for (int i = 0;i<M;i++)
            for (int j = 0;j < N;j++) 
            {
                if (field[i][j] == 0) continue;
                sprite.setTextureRect(sf::IntRect({ field[i][j] * 18, 0 }, { 18, 18 }));
                sprite.setPosition({ j * 18.f, i * 18.f });
                window.draw(sprite);
            }

        //------------------------DRAW FIGURES-------------------------------
        
        for (int i = 0;i < 4;i++) 
        {
            sprite.setTextureRect(sf::IntRect({ colorNum * 18, 0 }, { 18, 18 }));
            sprite.setPosition({ a[i].x * 18.f, a[i].y * 18.f });
            window.draw(sprite);
        }
       
        window.display();
    }
}