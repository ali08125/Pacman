#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <info.hpp>
#include <vector>

class Map
{
private:
    std::array<std::string, Height> sketch;
    std::array< std::array<sf::RectangleShape, Width>, Height> map;
    std::vector<sf::CircleShape> points;

    void initMap();

public:
    Map();
    void draw(sf::RenderWindow & window);
    std::array< std::array<sf::RectangleShape, Width>, Height> getMap() { return map; };
    
};