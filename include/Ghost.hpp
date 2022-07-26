#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>

class Ghost
{
private:
    sf::RectangleShape ghost;
    int dir;
    
    void initGhosts();
public:
    Ghost();
    void update(std::array<std::array<sf::RectangleShape, Width>, Height> map, sf::Vector2f pacmanPos);
    void draw(sf::RenderWindow &window);

    sf::RectangleShape getGhost() { return ghost; };
};