#include <SFML/Graphics.hpp>
#include <Map.hpp>
#include <Pacman.hpp>

using namespace sf;

int main()
{
    Map map;
    Pacman pacman;
    
    RenderWindow window(VideoMode(Width * CellSize, Height * CellSize), "PacMan");
    window.setFramerateLimit(120);
    
    Event event;
    while (window.isOpen())
    {
        
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

        std::vector<sf::CircleShape> temp = map.getPoint();
        pacman.update(map.getMap(), temp);
        map.setPoint(temp);

        map.draw(window);
        pacman.draw(window);

        window.display();
		       
    }
}