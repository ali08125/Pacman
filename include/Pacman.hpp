#pragma once

#include <SFML/Graphics.hpp>

class Pacman
{
private:
    sf::CircleShape player;

    
    void initPacman();

public:
    Pacman();
};