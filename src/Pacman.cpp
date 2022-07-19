#include <Pacman.hpp>
#include <info.hpp>

using namespace sf;

Pacman::Pacman()
{
    this->initPacman();
}

void Pacman::initPacman()
{
    Pos.x = 0;
    Pos.y = 0;
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
    Pos.x = x * CellSize;
    Pos.y = y * CellSize;
    //player.setPosition(Vector2f(x * CellSize, y * CellSize));
}