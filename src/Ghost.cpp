#include <Ghost.hpp>
#include <Collision.hpp>

using namespace sf;

Ghost::Ghost()
{
    initGhosts();
}

void Ghost::initGhosts()
{
    dir = -1;
    ghost.setFillColor(Color::Red);
    ghost.setSize(Vector2f(CellSize, CellSize));
    ghost.setPosition(Vector2f(10 * CellSize, 7 * CellSize));
}

void Ghost::update(std::array<std::array<RectangleShape, Width>, Height> map, sf::Vector2f pacmanPos)
{
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

    if(Keyboard::isKeyPressed(Keyboard::D))
    {
        if (wall[0] == 0)
        {
            dir = 0;
        }
    } else if(Keyboard::isKeyPressed(Keyboard::S))
    {
        if (wall[1] == 0)
        {
            dir = 1;
        }
    } else if(Keyboard::isKeyPressed(Keyboard::A))
    {   
        if (wall[2] == 0)
        {
            dir = 2;
        }
    } else if(Keyboard::isKeyPressed(Keyboard::W))
    {
        if (wall[3] == 0)
        {
            dir = 3;
        }
    }

    if (wall[dir] == 0)
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