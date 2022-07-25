#pragma once

#include <SFML/Graphics.hpp>

class Ghost
{
private:
    sf::RectangleShape ghost;
    
    void initGhosts();
public:
    Ghost();
    void update();
    void draw(sf::RenderWindow &window);
};