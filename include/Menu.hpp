#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
private:
    sf::Font font;
    sf::Text score;
    sf::Text level;
    sf::Text levelUp;

    void initMenu();
public:
    Menu();
    void levelUpScreen(sf::RenderWindow &window, int level);
    void draw(sf::RenderWindow &window, int score, int level);
};