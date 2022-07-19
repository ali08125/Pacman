#include <Pacman.hpp>
#include <info.hpp>

using namespace sf;

Pacman::Pacman()
{
    this->initPacman();
}

void Pacman::initPacman()
{
    player.setRadius(CellSize / 2);
    player.setFillColor(Color::Yellow);
}

void Pacman::draw(RenderWindow & window)
{
    window.draw(player);
}