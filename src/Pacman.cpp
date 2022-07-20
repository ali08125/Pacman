#include <Pacman.hpp>
#include <info.hpp>

using namespace sf;

Pacman::Pacman()
{
    this->initPacman();
}

void Pacman::initPacman()
{
    Pos.x = 9 * CellSize;
    Pos.y = 10 * CellSize;
    player.setRadius(CellSize / 2);
    player.setFillColor(Color::Yellow);
    player.setPosition(Pos);
    dir = 0;
}

void Pacman::draw(RenderWindow & window)
{
    player.setPosition(Pos);
    window.draw(player);
}

void Pacman::setPos(float x, float y)
{
    Pos.x += x;
    Pos.y += y;
}

void Pacman::move(std::vector<sf::RectangleShape> Walls, float dt)
{
    Vector2f position;
    FloatRect nextPos;

    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        dir = 1;
        position.x += Speed * dt;
        //setPos(Speed, 0);
    } else if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        dir = 2;
        position.y += Speed * dt;
        //setPos(0, Speed);
    } else if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        dir = 3;
        position.x -= Speed * dt;
        //setPos(-Speed, 0);
    } else if(Keyboard::isKeyPressed(Keyboard::Up))
    {
        dir = 4;
        position.y -= Speed * dt;
        //setPos(0, -Speed);
    } else
    {
        switch (dir)
        {
        case 1:
            position.x += Speed * dt;
            //setPos(Speed, 0);
            break;
        case 2:
            position.y += Speed * dt;
            //setPos(0, Speed);
            break;
        case 3:
            position.x -= Speed * dt;
            //setPos(-Speed, 0);
            break;
        case 4:
            position.y -= Speed * dt;
            //setPos(0, -Speed);
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
            position.x = 0;
            position.y = 0;
        }
        
    }
    
    setPos(position.x, position.y);
}