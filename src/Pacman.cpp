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

void Pacman::move()
{
    if(Keyboard::isKeyPressed(Keyboard::Right))
    {
        dir = 1;
        setPos(Speed, 0);
    } else if(Keyboard::isKeyPressed(Keyboard::Down))
    {
        dir = 2;
        setPos(0, Speed);
    } else if(Keyboard::isKeyPressed(Keyboard::Left))
    {
        dir = 3;
        setPos(-Speed, 0);
    } else if(Keyboard::isKeyPressed(Keyboard::Up))
    {
        dir = 4;
        setPos(0, -Speed);
    } else
    {
        switch (dir)
        {
        case 1:
            setPos(Speed, 0);
            break;
        case 2:
            setPos(0, Speed);
            break;
        case 3:
            setPos(-Speed, 0);
            break;
        case 4:
            setPos(0, -Speed);
            break;
        }
    }
}