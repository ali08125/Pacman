#include <SFML/Graphics.hpp>
#include <Map.hpp>
#include <Pacman.hpp>
#include <Text1.hpp>
#include <Ghost.hpp>

using namespace sf;

int main()
{
    Map map;
    Pacman pacman;
    Ghost ghost;
    Text1 text;
    
    RenderWindow window(VideoMode(Width * CellSize, Height * CellSize), "PacMan");
    window.setFramerateLimit(120);
    //window.setView();
    
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
        ghost.draw(window);
        pacman.draw(window);
        text.draw(window, pacman.getScore());

        window.display();
		       
    }
}