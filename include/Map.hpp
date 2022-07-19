#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>
#include <array>
#include <iostream>
#include <Pacman.hpp>

class Map
{
private:
    std::array<std::string, Height> sketch;
    Pacman pacman;

    void initMap();

public:
    Map();
    void draw(sf::RenderWindow & window);
    
};