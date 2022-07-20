#pragma once

#include <SFML/Graphics.hpp>
#include <info.hpp>
#include <array>
#include <iostream>
#include <Pacman.hpp>
#include <vector>

class Map
{
private:
    std::array<std::string, Height> sketch;
    Pacman pacman;
    std::vector<sf::RectangleShape> Walls;

    void initMap();

public:
    Map();
    void draw(sf::RenderWindow & window, float dt);
    
};