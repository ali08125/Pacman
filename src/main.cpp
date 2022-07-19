#include <SFML/Graphics.hpp>
#include <Map.hpp>

using namespace sf;

int main()
{
    RenderWindow window(VideoMode(Width * CellSize, Height * CellSize), "PacMan");
    Map map;

    while (window.isOpen())
    {
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

        //Draw
        map.drawMap(window);

        window.display();
    }
    

}