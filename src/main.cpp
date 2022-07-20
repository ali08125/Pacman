#include <SFML/Graphics.hpp>
#include <Map.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(Width * CellSize, Height * CellSize), "PacMan");
    window.setFramerateLimit(60);
    Map map;

    float dt;
    Clock dt_clock;

    while (window.isOpen())
    {
        dt = dt_clock.restart().asSeconds();
       // std::cout << dt << "\n";

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
            {
                window.close();
            }
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape)
            {
                window.close();
            }
        }

        window.clear();

        map.draw(window, dt);

        window.display();
    }
    

}