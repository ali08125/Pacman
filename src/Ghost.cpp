#include <Ghost.hpp>
#include <info.hpp>

using namespace sf;

Ghost::Ghost()
{
    initGhosts();
}

void Ghost::initGhosts()
{
    ghost.setFillColor(Color::Red);
    ghost.setSize(Vector2f(CellSize, CellSize));
    ghost.setPosition(Vector2f(10 * CellSize, 7 * CellSize));
}

void Ghost::update()
{

}

void Ghost::draw(sf::RenderWindow &window)
{
    window.draw(ghost);
}