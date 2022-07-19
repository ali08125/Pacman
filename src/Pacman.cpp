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
    setPos(1, 0);
}