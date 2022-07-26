#pragma once

#include <SFML/Graphics.hpp>

class Text1
{
private:
    sf::Font font;
    sf::Text score;
    sf::Text level;

    void initText();
public:
    Text1();
    void draw(sf::RenderWindow &window, int score, int level);
};