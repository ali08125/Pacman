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

    Clock clock;
    Time time;
    
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

        if (pacman.createFruit())
        {
            map.createFruit();
            clock.restart();
            time = seconds(clock.getElapsedTime().asSeconds());
        }
        time = seconds(clock.getElapsedTime().asSeconds());

        std::vector<CircleShape> temp = map.getFood();
        std::vector<CircleShape> temp1 = map.getPowerFood();
        std::vector<CircleShape> temp2 = map.getFruit();

        pacman.update(map.getMap(), temp, temp1, ghost.getGhost(), map.checkEndLevel()
        , map.getLevel(), temp2);

        map.setFood(temp);
        map.setPowerFood(temp1);
        map.setFruit(temp2);
        
        map.update(time);

        //ghost.update(map.getMap(), pacman.getPos(), pacman.getGhostCollision());

        map.draw(window);
        //ghost.draw(window);
        pacman.draw(window);
        text.draw(window, pacman.getScore(), map.getLevel());

        window.display(); 
    }
}