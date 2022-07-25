#pragma once

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <vector>
#include <info.hpp>

class Map
{
private:
    std::array<std::string, Height> sketch;
    std::vector<sf::RectangleShape> map;

    void initMap();

public:
    Map();
    void draw(sf::RenderWindow & window);
    
};