#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Pacman
{
private:
    sf::CircleShape player;
    sf::Vector2f Pos;
    int dir;


    void initPacman();

public:
    Pacman();
    void draw(sf::RenderWindow & window);
    void setPos(float x, float y);
    void move(std::vector<sf::RectangleShape> Walls, float dt);
};