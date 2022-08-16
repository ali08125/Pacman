#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::Font font;
    sf::Text score;
    sf::Text level;

    void initMenu();
public:
    Menu();
    void draw(sf::RenderWindow &window, int score, int level);
};