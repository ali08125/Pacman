#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>

class Ghost
{
private:
    sf::RectangleShape ghost;
    int dir;
    
    void initGhosts();
    int chooseDir(sf::Vector2f pacmanPos, std::array<bool, 4> wall);
    int scatterMode(std::array<bool, 4> wall);
public:
    Ghost();
    void update(std::array<std::array<sf::RectangleShape, Width>, Height> map, sf::Vector2f pacmanPos, bool accident);
    void draw(sf::RenderWindow &window);

    sf::RectangleShape getGhost() { return ghost; };
};