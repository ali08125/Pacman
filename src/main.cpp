#include <SFML/Graphics.hpp>
#include <Map.hpp>
#include <Pacman.hpp>
#include <Menu.hpp>
#include <Ghost.hpp>

using namespace sf;

int main()
{
    Map map;
    Pacman pacman;
    Ghost ghost;
    Menu menu;

    Clock clock;
    Time time;

    RenderWindow window(VideoMode(Width * CellSize, Height * CellSize), "PacMan");
    window.setFramerateLimit(60);

    Event event;
    clock.restart();

    bool click = false;

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

        //Show menu
        if (click == false)
        {
            int tmp = 0;
            while (1 && tmp == 0)
            {
                int choice = menu.gameMenu(window);
                switch (choice)
                {
                case 0:
                    continue;
                    break;
                case 1:
                    tmp = 1;
                    break;
                case 3:
                    exit(EXIT_SUCCESS);
                    break;
                }
            }
            click = true;
        }
        
        window.clear();

        //Start playing game

        if (pacman.createFruit())
        {
            map.createFruit(pacman.getPacman());
            clock.restart();
            time = seconds(clock.getElapsedTime().asSeconds());
        }
        time = seconds(clock.getElapsedTime().asSeconds());


        std::vector<CircleShape> temp = map.getFood();
        std::vector<CircleShape> temp1 = map.getPowerFood();
        std::vector<Sprite> temp2 = map.getFruit();

        pacman.update(map.getMap(), temp, temp1, ghost.getGhost(), map.checkEndLevel()
        , map.getLevel(), temp2);

        map.setFood(temp);
        map.setPowerFood(temp1);
        map.setFruit(temp2);

        
        map.update(time);

        bool levelUp = pacman.getLevelUp();
        ghost.update(map.getMap(), pacman.getPos(), pacman.getGhostCollision()
        ,pacman.getStart(), pacman.getPowerFoodInfo(), pacman.getGhostEncounter(), levelUp);

        if (levelUp)
        {
            menu.levelUpScreen(window, map.getLevel());
        }
    
        map.draw(window);
        ghost.draw(window);
        pacman.draw(window);
        menu.draw(window, pacman.getScore(), map.getLevel(), pacman.getHealth());
        
        window.display(); 

        //Death
        if (pacman.getDeath())
        {
            if(menu.deathScreen(window, pacman.getScore()))
            {
                pacman.resetPacman();
                map.resetMap();
               // ghost.resetGhosts();
                click = false;
                continue;
            }
        }
    }

    return 0;
}