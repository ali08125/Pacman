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
    
    initGhosts();
}

void Ghost::initGhosts()
{    
    //Reset everything
    for (size_t i = 0; i < 4; i++)
    {   
        clock[i].restart();
        scaredTimeWink[i].restart();
        wink[i] = 0;
        ghostDir[i] = -1;
        frame[i] = 0;
        scared[i] = false;
        eaten[i] = false;

        switch (i)
        {
        case 0://Red
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(10 * CellSize + 15, 8 * CellSize + 15));        
            break;
        case 1://Pink
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(10 * CellSize + 15, 10 * CellSize + 15));
            break;
        case 2://Orange
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(11 * CellSize + 15, 10 * CellSize + 15));
            break;
        case 3://Blue
            ghost[i].setTexture(ghostTexture[i][0][0]);
            ghost[i].setScale(Vector2f(0.3, 0.3));
            ghost[i].setOrigin(Vector2f(50, 50));
            ghost[i].setPosition(Vector2f(9 * CellSize + 15, 10 * CellSize + 15));
            break;
        }
    }
}

void Ghost::resetGhosts()
{
    initGhosts();
}

void Ghost::update(array<array<RectangleShape, Width>, Height> map
, Vector2f pacmanPos, array<bool, 4> accident, bool start, bool eatPowerFood, int eatGhost, bool levelUp)
{   
    if (levelUp)
    {
        resetGhosts();
    }

    //If one of the ghosts hits Pacman in normal mode, the ghosts will be reset
    for (size_t i = 0; i < 4; i++)
    {
        if (accident[i] && !scared[i])
        {
            resetGhosts();
        }
    }
    //If the player did not press a key, do nothing
    if (!start)
    {
        return;
    } 
    //If Pacman eats a powerFood, the ghosts will go into a fear
    if (eatPowerFood)
    {  
        scaredTime.restart();
        for (size_t i = 0; i < 4; i++)
        {            
            scared[i] = true;
            wink[i] = 0;
        }
    }
    //After 5 seconds of fear mode, the ghosts return to normal mode
    if (scaredTime.getElapsedTime().asSeconds() >= 5 && scaredTime.getElapsedTime().asSeconds() <= 6)
    {
        for (size_t i = 0; i < 4; i++)
        {
            scared[i] = false;
        }   
    }

    array<bool, 4> wall;//Checking the wall on 4 sides of ghost
    Vector2f position;//Position changes

    for (size_t i = 0; i < 4; i++)
    {
        // Collision Right
        wall[0] = collision(ghost[i].getPosition().x - 15 + Speed, ghost[i].getPosition().y - 15, map);
        // Collision Down
        wall[1] = collision(ghost[i].getPosition().x - 15, ghost[i].getPosition().y + Speed - 15, map);
        // Collision Left
        wall[2] = collision(ghost[i].getPosition().x - 15 - Speed, ghost[i].getPosition().y - 15, map);
        // Collision Up
        wall[3] = collision(ghost[i].getPosition().x - 15, ghost[i].getPosition().y - Speed - 15, map, 1);

        position.x = 0;
        position.y = 0;

        //If the ghost is eaten by Pacman in fear mode, reset it
        if (eatGhost == i)
        {
            switch (i)
            {
            case 0://Red
                ghostDir[i] = -1;
                scared[i] = false;
                ghost[i].setTexture(ghostTexture[i][0][0]);
                ghost[i].setPosition(Vector2f(10 * CellSize + 15, 8 * CellSize + 15));      
                break;
            case 1://Pink
                ghostDir[i] = -1;
                scared[i] = false;
                ghost[i].setTexture(ghostTexture[i][0][0]);
                ghost[i].setPosition(Vector2f(10 * CellSize + 15, 10 * CellSize + 15));
                break;
            case 2://Orange
                ghostDir[i] = -1;
                scared[i] = false;
                ghost[i].setTexture(ghostTexture[i][0][0]);
                ghost[i].setPosition(Vector2f(11 * CellSize + 15, 10 * CellSize + 15));
                break;
            case 3://Blue
                ghostDir[i] = -1;
                scared[i] = false;
                ghost[i].setTexture(ghostTexture[i][0][0]);
                ghost[i].setPosition(Vector2f(9 * CellSize + 15, 10 * CellSize + 15));
                break;
            }
        } else
        {
            //Determining the direction of movement randomly
            ghostDir[i] = scatterMode(wall, ghostDir[i]);
        }
        //If it did not hit the wall, it would move
        if (wall[ghostDir[i]] == 0 && ghostDir[i] != -1)
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
        animation(ghostDir[i], i, scared[i]);

        //Use tunnel
        if (ghost[i].getPosition().x - 15 >= CellSize * Width)//Exit from right side of the map
        {
            position.x = 15;
            ghost[i].setPosition(Vector2f(position.x, ghost[i].getPosition().y));
            
        } else if (ghost[i].getPosition().x - 15 <= -CellSize)//Exit from left side of the map
        {
            position.x = Width * CellSize - 15;
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
    //Scared time animation
    if (scared && scaredTime.getElapsedTime().asSeconds() <= 5)
    {
        if (scaredTimeWink[i].getElapsedTime().asSeconds() > 0.09)
        {
            scaredTimeWink[i].restart();
            //The ghost flashes after 2 seconds of fear time
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
        //Animate ghost in normal mode
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
        //Random number generation
        random = rand() % 4;
        //Do not hit the wall and do not change direction 180 degrees
        if (!wall[random] && (random != dir - 2 && random != dir + 2))
        {
            return random;
        }
        //Stop if it fails to find a suitable number more than 50 times
        if (try1 > 50)
        {
            return -1;   
        }
    }
    return -1;
}