#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>

class Ghost
{
private:
    sf::RectangleShape ghost;
    
    void initGhosts();
public:
    Ghost();
    void update(std::array<std::array<sf::RectangleShape, Width>, Height> map);
    void draw(sf::RenderWindow &window);

    sf::RectangleShape getGhost() { return ghost; };
};