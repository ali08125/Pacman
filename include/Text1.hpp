#pragma once

#include <SFML/Graphics.hpp>

class Text1
{
private:
    sf::Font font;
    sf::Text text;

    void initText();
public:
    Text1();
    void draw(sf::RenderWindow &window);
};