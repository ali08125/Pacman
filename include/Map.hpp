#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>
#include <array>
#include <iostream>

class Map
{
private:
    std::array<std::string, Height> sketch;
    void initMap();

public:
    Map();
    void draw(sf::RenderWindow & window);
    
};