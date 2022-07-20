#include <Pacman.hpp>
#include <info.hpp>
#include <iostream>

using namespace sf;

Pacman::Pacman()
{
    this->initPacman();
}

void Pacman::initPacman()
{
    Pos.x = 9 * CellSize;
    Pos.y = 10 * CellSize;
    player.setRadius(CellSize / 2 - 1);
    player.setFillColor(Color::Yellow);
    player.setPosition(Pos);
    dir = 0;
}

void Pacman::draw(RenderWindow & window)
{
    window.draw(player);
}

void Pacman::move(std::vector<sf::RectangleShape> Walls, float dt)
{
    Vector2f position;
    FloatRect nextPos;
    nextDir = dir;

    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        dir = 1;
        position.x += Speed * dt;
    } else if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        dir = 2;
        position.y += Speed * dt;
    } else if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        dir = 3;
        position.x -= Speed * dt;
    } else if(Keyboard::isKeyPressed(Keyboard::Up))
    {
        dir = 4;
        position.y -= Speed * dt;
    } else
    {
        switch (dir)
        {
        case 1:
            position.x += Speed * dt;
            break;
        case 2:
            position.y += Speed * dt;
            break;
        case 3:
            position.x -= Speed * dt;
            break;
        case 4:
            position.y -= Speed * dt;
            break;
        }
    }
    // collision
    for(auto & wall : Walls)
    {
        FloatRect playerBounds = player.getGlobalBounds();
        FloatRect wallBounds = wall.getGlobalBounds();

        nextPos = playerBounds;
        nextPos.left += position.x;
        nextPos.top += position.y;

        if (wallBounds.intersects(nextPos))
        {
            // Right
            if (playerBounds.left < wallBounds.left
                && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                && playerBounds.top < wallBounds.top + wallBounds.height
                && playerBounds.top + playerBounds.height > wallBounds.top
            )
            {
                position.x = 0;
                player.setPosition(wallBounds.left - playerBounds.width, playerBounds.top);                
            }
            // Bottom
            else if (playerBounds.top < wallBounds.top
                && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                && playerBounds.left < wallBounds.left + wallBounds.width
                && playerBounds.left + playerBounds.width > wallBounds.left
            )
            {
                position.y = 0;
                player.setPosition(player.getPosition().x, wallBounds.top - playerBounds.height);                
            }
            
        }
    }
    player.move(position.x, position.y);
}