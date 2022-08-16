#include <Ghost.hpp>
#include <Collision.hpp>
#include <iostream>

using namespace sf;
using namespace std;

Ghost::Ghost()
{
    srand(time(0));

    //Load textures
    for (size_t k = 0; k < 4; k++)
    {
        for (size_t i = 0; i < 4; i++)
        {
            for (size_t j = 0; j < 2; j++)
            {
                string ghostColor;

                switch (k)
                {
                case 0://Red
                    ghostColor = "../Photo/ghost/red";
                    break;
                case 1://Pink
                    ghostColor = "../Photo/ghost/pink";
                    break;
                case 2://Orange
                    ghostColor = "../Photo/ghost/orange";
                    break;
                case 3://Blue
                    ghostColor = "../Photo/ghost/blue";
                    break;
                }

                ghostColor += to_string(i) + to_string(j) + ".png";
                if (!ghostTexture[k][i][j].loadFromFile(ghostColor))
                cout << "can not load " << ghostColor << endl;
            }
        }
    }
    
    for (size_t i = 0; i < 2; i++)
    { 
        for (size_t j = 0; j < 2; j++)
        {
            string ghostState = "../Photo/ghost/scared";
            ghostState += to_string(i) + to_string(j) + ".png";
            if(!scaredGhostTexture[i][j].loadFromFile(ghostState))
                cout << "can not load " << ghostState << endl;
        }
        
    }
    
    if(!eyes.loadFromFile("../Photo/ghost/eyes.png"))
                cout << "can not load eyes" << endl;
    
    initGhosts();
}

void Ghost::initGhosts()
{    
    for (size_t i = 0; i < 4; i++)
    {
        frame[i] = 0;
        clock[i].restart();
        wink[i] = 0;
        
        switch (i)
        {
        case 0://Red
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(10 * CellSize + 15, 7 * CellSize + 15));        
            break;
        case 1://Pink
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(10 * CellSize + 15, 9 * CellSize + 15));
            break;
        case 2://Orange
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(11 * CellSize + 15, 9 * CellSize + 15));
            break;
        case 3://Blue
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(9 * CellSize + 15, 9 * CellSize + 15));
            break;
        }
        ghostDir[i] = -1;
    }
}

void Ghost::update(array<array<RectangleShape, Width>, Height> map
, Vector2f pacmanPos, array<bool, 4> accident, bool start, bool eatPowerFood)
{   
    if (!scared && eatPowerFood)
    {  
        scaredTime.restart();
    }
    this->scared = eatPowerFood;

    for (size_t i = 0; i < 4; i++)
    {
        if (accident[i])
        {
            initGhosts();
        }
    }
    
    if (!start)
    {
        return;
    }
    
    array<array<bool, 4>, 4> wall;

    Vector2f position;

    for (size_t i = 0; i < 4; i++)
    {
        // Collision Right
        wall[i][0] = collision(ghost[i].getPosition().x - 15 + Speed, ghost[i].getPosition().y - 15, map);
        // Collision Down
        wall[i][1] = collision(ghost[i].getPosition().x - 15, ghost[i].getPosition().y + Speed - 15, map);
        // Collision Left
        wall[i][2] = collision(ghost[i].getPosition().x - 15 - Speed, ghost[i].getPosition().y - 15, map);
        // Collision Up
        wall[i][3] = collision(ghost[i].getPosition().x - 15, ghost[i].getPosition().y - Speed - 15, map, 1);

        position.x = 0;
        position.y = 0;

        //dir = chaseMode(pacmanPos, wall);
        ghostDir[i] = scatterMode(wall[i], ghostDir[i]);

        if (wall[i][ghostDir[i]] == 0 && ghostDir[i] != -1)
        { 
            switch (ghostDir[i])
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

        ghost[i].move(position.x, position.y);
        animation(ghostDir[i], i, eatPowerFood);

        // Exit from a side and enter from the other side
        if (ghost[i].getPosition().x - 15 >= CellSize * Width)
        {
            position.x = Speed - CellSize + 15;
            ghost[i].setPosition(Vector2f(position.x, ghost[i].getPosition().y));
            
        } else if (ghost[i].getPosition().x - 15 <= -CellSize)
        {
            position.x = Width * CellSize - Speed + 15;
            ghost[i].setPosition(Vector2f(position.x, ghost[i].getPosition().y));
        }
    }

}

void Ghost::draw(sf::RenderWindow &window)
{
    for (size_t i = 0; i < 4; i++)
    {
        window.draw(ghost[i]);
    }
}

void Ghost::animation(int dir, int i, bool scared)
{
    if (scared)
    {
        if (scaredTimeWink[i].getElapsedTime().asSeconds() > 0.09)
        {
            scaredTimeWink[i].restart();
            if (scaredTime.getElapsedTime().asSeconds() >= 2)
            {
                if (wink[i] == 0)
                {
                    wink[i] = 1;
                } else
                {
                    wink[i] = 0;
                }
            }
        }

        if (clock[i].getElapsedTime().asSeconds() > 0.05)
        {
            clock[i].restart();
            ghost[i].setTexture(scaredGhostTexture[wink[i]][frame[i]]);

            if (frame[i] == 0)
                frame[i] = 1;
            else
                frame[i] = 0;
        } 
    } else
    {
        if (clock[i].getElapsedTime().asSeconds() > 0.05)
        {
            clock[i].restart();
            ghost[i].setTexture(ghostTexture[i][dir][frame[i]]);

            if (frame[i] == 0)
                frame[i] = 1;
            else
                frame[i] = 0;
        } 
    }
}

int Ghost::scatterMode(array<bool, 4> wall, int dir)
{
    int try1 = 0;
    int random;
    while (1)
    {
        try1++;
        random = rand() % 4;
        if (!wall[random] && (random != dir - 2 && random != dir + 2))
        {
            return random;
        }

        if (try1 > 50)
        {
            return -1;   
        }
    }
    return -1;
}

int Ghost::chaseMode(Vector2f pacmanPos, std::array<bool, 4> wall)
{
    /*
    int random = rand() % 2;

    // Pacman is the right top of the ghost
    if (pacmanPos.x > ghost.getPosition().x && pacmanPos.y < ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.y < ghost.getPosition().y && wall[3] == 0) && dir != 1)
        {
            // Up
            return 3;
        } else if (random == 1 && (pacmanPos.x > ghost.getPosition().x && wall[0] == 0) && dir != 2)
        {
            // Right
            return 0;
        } else if (wall[2] == 0 && dir != 0)
        {
            // Left
            return 2;
        } else if (wall[1] == 0 && dir != 3)
        {
            // Down
            return 1;
        }
    }

    // Pacman is the left top of the ghost
    if (pacmanPos.x < ghost.getPosition().x && pacmanPos.y < ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.y < ghost.getPosition().y && wall[3] == 0) && dir != 1)
        {
            // Up
            return 3;
        } else if (random == 1 && (pacmanPos.x < ghost.getPosition().x && wall[2] == 0) && dir != 0)
            {
                // Left
                return 2;
            } else if (wall[1] == 0 && dir != 3)
            {
                // Down
                return 1;
            } else if (wall[0] == 0 && dir != 2)
            {
                // Right
                return 0;
            }
    }

    // Pacman is the top of the ghost
    if (pacmanPos.x == ghost.getPosition().x && pacmanPos.y < ghost.getPosition().y)
    {
        if ((pacmanPos.y < ghost.getPosition().y && wall[3] == 0) && dir != 1)
        {
            // Up
            return 3;
        } else if (random == 0 && wall[2] == 0 && dir != 0)
        {
            // Left
            return 2;
        } else if (random == 1 && wall[1] == 1 && dir != 3)
        {
            // Down
            return 1;
        } else if (wall[0] == 0 && dir != 2)
        {
            // Right
            return 0;
        }   
    }

    // Pacman is the right bottom of the ghost
    if (pacmanPos.x > ghost.getPosition().x && pacmanPos.y > ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.y > ghost.getPosition().y && wall[1] == 0) && dir != 3)
        {
            // Down
            return 1;
        } else if (random == 1 && (pacmanPos.x > ghost.getPosition().x && wall[0] == 0) && dir != 2)
        {
            // Right
            return 0;
        } else if (wall[2] == 0 && dir != 0)
        {
            // Left
            return 2;
        } else if (wall[3] == 0 && dir != 1)
        {
            // Up
            return 3;
        }
    }

    // Pacman is the left bottom of the ghost
    if (pacmanPos.x < ghost.getPosition().x && pacmanPos.y > ghost.getPosition().y)
    {
        if (random == 0 && (pacmanPos.x < ghost.getPosition().x && wall[2] == 0) && dir != 0)
        {
            // Left
            return 2;
        } else if (random == 1 && (pacmanPos.y > ghost.getPosition().y && wall[1] == 0) && dir != 3)
        {
            // Down
            return 1;
        } else if (wall[0] == 0 && dir != 2)
        {
            // Right
            return 0;
        } else if (wall[3] == 0 && dir != 1)
        {
            // Up
            return 3;
        }
    }

    // Pacman is the bottom of the ghost
    if (pacmanPos.x == ghost.getPosition().x && pacmanPos.y > ghost.getPosition().y)
    {
        if ((wall[1] == 0) && dir != 3)
        {
            // Down
            return 1;
        } else if (wall[2] == 0 && dir != 0)
        {
            // Left
            return 2;
        } else if (wall[0] == 0 && dir != 2)
        {
            // Right
            return 0;
        } else if (wall[3] == 0 && dir != 1)
        {
            // Up
            return 3;
        }   
    }

    // Pacman is the left of the ghost
    if (pacmanPos.x < ghost.getPosition().x && pacmanPos.y == ghost.getPosition().y)
    {
        if (wall[2] == 0 && dir != 0)
        {
            // Left
            return 2;
        } else if (wall[1] == 0 && dir != 3)
        {
            // Down
            return 1;
        } else if (wall[3] == 0 && dir != 1)
        {
            // Up
            return 3;
        } else if (wall[0] == 0 && dir != 2)
        {
            // Right
            return 0;
        }    
    }

    // Pacman is the right of the ghost
    if (pacmanPos.x > ghost.getPosition().x && pacmanPos.y == ghost.getPosition().y)
    {
        if (wall[0] == 0 && dir != 2)
        {
            // Right
            return 0;
        } else if (wall[1] == 0 && dir != 3)
        {
            // Down
            return 1;
        } else if (wall[3] == 0 && dir != 1)
        {
            // Up
            return 3;
        } else if (wall[2] == 0 && dir != 0)
        {
            // Left
            return 2;
        }   
    }
    */
    return -1;
}