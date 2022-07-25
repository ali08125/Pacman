#include <Ghost.hpp>
#include <Collision.hpp>

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

void Ghost::update(std::array<std::array<RectangleShape, Width>, Height> map)
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

    if (wall[0] == 0)
    {
        ghost.move(0.2, 0); 
    }
    
    

}

void Ghost::draw(sf::RenderWindow &window)
{
    window.draw(ghost);
}