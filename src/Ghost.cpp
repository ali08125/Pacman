#include <Ghost.hpp>
#include <Collision.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Ghost::Ghost()
{
    srand(time(0));
    initGhosts();
}

void Ghost::initGhosts()
{
    dir = -1;
    ghost.setFillColor(Color::Red);
    ghost.setSize(Vector2f(CellSize, CellSize));
    ghost.setPosition(Vector2f(10 * CellSize, 7 * CellSize));
}

void Ghost::update(array<array<RectangleShape, Width>, Height> map, Vector2f pacmanPos, bool accident)
{
    if (accident)
    {
        initGhosts();
    }
    
    std::array<bool, 4> wall;

    // Collision Right
    wall[0] = collision(ghost.getPosition().x + (Speed), ghost.getPosition().y, map);
    // Collision Down
    wall[1] = collision(ghost.getPosition().x, ghost.getPosition().y + (Speed), map);
    // Collision Left
    wall[2] = collision(ghost.getPosition().x - (Speed), ghost.getPosition().y, map);
    // Collision Up
    wall[3] = collision(ghost.getPosition().x, ghost.getPosition().y - (Speed), map);

    Vector2f position;
    position.x = 0;
    position.y = 0;
    
    dir = chooseDir(pacmanPos, wall);

    if (wall[dir] == 0 && dir != -1)
    { 
        switch (dir)
        {
        case 0:
            position.x += Speed;
            break;
        case 1:
            position.y += Speed;
            break;
        case 2:
            position.x -= Speed;
            break;
        case 3:
            position.y -= Speed;
            break;
        }
    }
    
    ghost.move(position.x, position.y);   

    
    // Exit from a side and enter from the other side
    if (ghost.getPosition().x >= CellSize * Width)
    {
        position.x = Speed - CellSize;
        ghost.setPosition(Vector2f(position.x, ghost.getPosition().y));
        
    } else if (ghost.getPosition().x <= -CellSize)
    {
        position.x = Width * CellSize - Speed;
        ghost.setPosition(Vector2f(position.x, ghost.getPosition().y));
    }

}

void Ghost::draw(sf::RenderWindow &window)
{
    window.draw(ghost);
}

int Ghost::chooseDir(Vector2f pacmanPos, std::array<bool, 4> wall)
{
    int random = rand() % 2;
    cout << random << endl;

    // Pacman is the right top of the ghost
    if (pacmanPos.x > ghost.getPosition().x && pacmanPos.y < ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.y < ghost.getPosition().y && wall[3] == 0) && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        } else if (random == 1 && (pacmanPos.x > ghost.getPosition().x && wall[0] == 0) && (dir != 2 || wall[2] != 0))
        {
            // Right
            return 0;
        } else if (wall[2] == 0 && (dir != 0 || wall[0] != 0))
        {
            // Left
            return 2;
        } else if (wall[1] == 0 && (dir != 3 || wall[3] != 0))
        {
            // Down
            return 1;
        }
    }

    // Pacman is the left top of the ghost
    if (pacmanPos.x < ghost.getPosition().x && pacmanPos.y < ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.y < ghost.getPosition().y && wall[3] == 0) && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        } else if (random == 1 && (pacmanPos.x < ghost.getPosition().x && wall[2] == 0) && (dir != 0 || wall[0] != 0))
            {
                // Left
                return 2;
            } else if (wall[1] == 0 && (dir != 3 || wall[3] != 0))
            {
                // Down
                return 1;
            } else if (wall[0] == 0 && (dir != 2 || wall[2] != 0))
            {
                // Right
                return 0;
            }
    }

    // Pacman is the top of the ghost
    if (pacmanPos.x == ghost.getPosition().x && pacmanPos.y < ghost.getPosition().y)
    {
        if ((pacmanPos.y < ghost.getPosition().y && wall[3] == 0) && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        } else if (random == 0 && wall[2] == 0 && (dir != 0 || wall[0] != 0))
        {
            // Left
            return 2;
        } else if (random == 1 && wall[1] == 1 && (dir != 3 || wall[3] != 0))
        {
            // Down
            return 1;
        } else if (wall[0] == 0 && (dir != 2 || wall[2] != 0))
        {
            // Right
            return 0;
        }   
    }

    // Pacman is the right bottom of the ghost
    if (pacmanPos.x > ghost.getPosition().x && pacmanPos.y > ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.y > ghost.getPosition().y && wall[1] == 0) && (dir != 3 || wall[3] != 0))
        {
            // Down
            return 1;
        } else if (random == 1 && (pacmanPos.x > ghost.getPosition().x && wall[0] == 0) && (dir != 2 || wall[2] != 0))
        {
            // Right
            return 0;
        } else if (wall[2] == 0 && (dir != 0 || wall[0] != 0))
        {
            // Left
            return 2;
        } else if (wall[3] == 0 && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        }
    }

    // Pacman is the left bottom of the ghost
    if (pacmanPos.x < ghost.getPosition().x && pacmanPos.y > ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.x < ghost.getPosition().x && wall[2] == 0) && (dir != 0 || wall[0] != 0))
        {
            // Left
            return 2;
        } else if (random == 1 && (pacmanPos.y > ghost.getPosition().y && wall[1] == 0) && (dir != 3 || wall[3] != 0))
        {
            // Down
            return 1;
        } else if (wall[0] == 0 && (dir != 2 || wall[2] != 0))
        {
            // Right
            return 0;
        } else if (wall[3] == 0 && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        }
    }

    // Pacman is the bottom of the ghost
    if (pacmanPos.x == ghost.getPosition().x && pacmanPos.y > ghost.getPosition().y)
    {
        if ((wall[1] == 0) && (dir != 3 || wall[3] != 0))
        {
            // Down
            return 1;
        } else if (wall[2] == 0 && (dir != 0 || wall[0] != 0))
        {
            // Left
            return 2;
        } else if (wall[0] == 0 && (dir != 2 || wall[2] != 0))
        {
            // Right
            return 0;
        } else if (wall[3] == 0 && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        }   
    }

    // Pacman is the left of the ghost
    if (pacmanPos.x < ghost.getPosition().x && pacmanPos.y == ghost.getPosition().y)
    {
        if (wall[2] == 0 && (dir != 0 || wall[0] != 0))
        {
            // Left
            return 2;
        } else if (wall[1] == 0 && (dir != 3 || wall[3] != 0))
        {
            // Down
            return 1;
        } else if (wall[3] == 0 && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        } else if (wall[0] == 0 && (dir != 2 || wall[2] != 0))
        {
            // Right
            return 0;
        }    
    }

    // Pacman is the right of the ghost
    if (pacmanPos.x > ghost.getPosition().x && pacmanPos.y == ghost.getPosition().y)
    {
        if (wall[0] == 0 && (dir != 2 || wall[2] != 0))
        {
            // Right
            return 0;
        } else if (wall[1] == 0 && (dir != 3 || wall[3] != 0))
        {
            // Down
            return 1;
        } else if (wall[3] == 0 && (dir != 1 || wall[1] != 0))
        {
            // Up
            return 3;
        } else if (wall[2] == 0 && (dir != 0 || wall[0] != 0))
        {
            // Left
            return 2;
        }   
    }
    return dir;
}